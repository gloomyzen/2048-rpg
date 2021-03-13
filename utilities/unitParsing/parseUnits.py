from __future__ import print_function
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
import json

SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']

def getSpreadSheetId():
    with open('parseSettings.json') as json_file:
        data = json.load(json_file)
        if not data['spreadsheetId']:
            print("spreadsheetId is not valid!")
        return data['spreadsheetId']


def main():
    spreadsheetId = getSpreadSheetId()
    # print('%s' % (spreadsheetId))
    # findRange = getFindRange()
    # print('%s' % (startRow))
    # dataStruct = getDataStruct()
    # parseSheet(spreadsheetId, findRange, dataStruct)

if __name__ == '__main__':
    main()