from googleapiclient.http import MediaIoBaseDownload
from googleapiclient.http import MediaFileUpload
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
import io
import os
import pickle
import sys
import hashlib
import datetime
import time
import platform

"""
https://developers.google.com/drive/api/v3/reference/files
"""

SCOPES = ['https://www.googleapis.com/auth/drive.metadata']
assetsStore = 'MBAssetsStore'


def get_creation_time(path):
    (mode, ino, dev, nlink, uid, gid, size, atime, mtime, ctime) = os.stat(str(path))
    return mtime


def md5(fname):
    hash_md5 = hashlib.md5()
    with open(fname, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()


def date_to_seconds(dateTime):
    return int(datetime.datetime.strptime(dateTime, "%Y-%m-%dT%H:%M:%S.%fZ").strftime("%s"))


def creation_date(path_to_file):
    if platform.system() == 'Windows':
        return int(os.path.getctime(path_to_file))
    else:
        stat = os.stat(path_to_file)
        try:
            return int(stat.st_birthtime)
        except AttributeError:
            return int(stat.st_mtime)


def set_file_timestamps(fname, modifiedTime):
    mtime = date_to_seconds(modifiedTime)
    set_file_modification_time(fname, mtime)


def set_file_modification_time(fname, newtime):
    # Set access time to same value as modified time,
    # since Drive API doesn't provide access time
    os.utime(fname, (newtime, newtime))


def main():
    creds = None
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file('credentials.json', SCOPES)
            creds = flow.run_local_server(port=1337)
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token, protocol=0)
    service = build('drive', 'v3', credentials=creds)

    folder_name = ''
    folder_id = ''
    location = '../Resources/'
    # if len(sys.argv) > 2:
    #     location = sys.argv[2]
    #     if location[-1] != '/':
    #         location += '/'

    folder = service.files().list(
        q=f"name contains '{assetsStore}' and mimeType='application/vnd.google-apps.folder'",
        fields='files(id, name, parents)').execute()

    total = len(folder['files'])
    if total != 1:
        print(f'{total} folders found')
        if total == 0:
            sys.exit(1)
        prompt = 'Please select the folder you want to download:\n\n'
        for i in range(total):
            prompt += f'[{i}]: {get_full_path(service, folder["files"][i])}\n'
        prompt += '\nYour choice: '
        choice = int(input(prompt))
        if 0 <= choice and choice < total:
            folder_id = folder['files'][choice]['id']
            folder_name = folder['files'][choice]['name']
        else:
            sys.exit(1)
    else:
        folder_id = folder['files'][0]['id']
        folder_name = folder['files'][0]['name']

    print(f'{folder_id} {folder_name}')
    download_folder(service, folder_id, location, folder_name)


def get_full_path(service, folder):
    if not 'parents' in folder:
        return folder['name']
    files = service.files().get(fileId=folder['parents'][0], fields='id, name, parents').execute()
    path = files['name'] + ' > ' + folder['name']
    while 'parents' in files:
        files = service.files().get(fileId=files['parents'][0], fields='id, name, parents').execute()
        path = files['name'] + ' > ' + path
    return path


def download_folder(service, folder_id, location, folder_name):
    if not os.path.exists(location + folder_name) and folder_name != assetsStore:
        os.makedirs(location + folder_name)
    # remove root folder name from path
    if folder_name != assetsStore:
        location += folder_name + '/'

    result = []
    page_token = None
    while True:
        files = service.files().list(
            q=f"'{folder_id}' in parents",
            fields='nextPageToken, files(id, name, mimeType, md5Checksum, modifiedTime, createdTime, trashedTime)',
            pageToken=page_token,
            pageSize=1000).execute()
        result.extend(files['files'])
        page_token = files.get("nextPageToken")
        if not page_token:
            break

    result = sorted(result, key=lambda k: k['name'])

    total = len(result)
    current = 1
    for item in result:
        file_id = item['id']
        filename = item['name']
        mime_type = item['mimeType']
        if "trashedTime" in item:
            continue
        print(f'{file_id} {filename} {mime_type} ({current}/{total})')
        if mime_type == 'application/vnd.google-apps.folder':
            download_folder(service, file_id, location, filename)
        elif not os.path.isfile(location + filename):
            download_file(service, file_id, location, filename, mime_type, item["modifiedTime"])
        else:
            external_file_size = item['md5Checksum']
            local_file_size = md5(location + filename)
            if external_file_size != local_file_size:
                local_m_timestamp = get_creation_time(location + filename)
                external_m_datetime = date_to_seconds(item["modifiedTime"])
                if local_m_timestamp >= external_m_datetime:
                    test = 'upload'
                    #todo upload files
                    file_metadata = {'name': filename}
                    media = MediaFileUpload(location + filename, mimetype=mime_type, resumable=True)
                    request = service.files().create(body=file_metadata, media_body=media)
                    response = None
                    while response is None:
                        status, response = request.next_chunk()
                        if status:
                            print("Uploaded %d%%." % int(status.progress() * 100))

                    print("Upload of {} is complete.".format(filename))

                    print ('File ID: %s' % request.get('id'))

                else:
                    download_file(service, file_id, location, filename, mime_type, item["modifiedTime"])
        current += 1
        # todo compare local files and folder in 'location' and upload then if item are missing
        #  https://developers.google.com/drive/api/v3/manage-uploads


def download_file(service, file_id, location, filename, mime_type, m_time):
    if 'vnd.google-apps' in mime_type:
        request = service.files().export_media(fileId=file_id,
                                               mimeType='application/pdf')
        filename += '.pdf'
    else:
        request = service.files().get_media(fileId=file_id, fields='size')
    fh = io.FileIO(location + filename, 'wb')
    downloader = MediaIoBaseDownload(fh, request, 1024 * 1024 * 1024)
    done = False
    while done is False:
        try:
            status, done = downloader.next_chunk()
        except:
            fh.close()
            os.remove(location + filename)
            sys.exit(1)
        print(f'\rDownload {int(status.progress() * 100)}%.', end='')
        sys.stdout.flush()
    set_file_timestamps(location + filename, m_time)
    print('')


if __name__ == '__main__':
    main()
