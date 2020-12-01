//https://github.com/Tencent/rapidjson/issues/1448
#if defined(_MSC_VER) && defined(GetObject)
#undef GetObject
#endif