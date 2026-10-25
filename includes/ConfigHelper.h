#pragma once
#include <eModelID.h>
#include <map>
#include <plugin.h>
#include <string>

struct ModelEnumMapping {
    const char *name;
    int id;
};

class ConfigHelper {
    std::string path;
    std::map<std::string, std::string> m_comments;
    void StoreComment(const char *sec, const char *key, const char *comment);

public:
    ConfigHelper(const std::string &iniPath);

    int ReadInt(const char *sec, const char *key, int def);
    std::string ReadString(const char *sec, const char *key, const std::string &def);
    int ReadModelArray(const char *sec, const char *key, int *outArray, int maxCount, const int *defaultArray);

    void WriteInt(const char *sec, const char *key, int val, const char *comment = nullptr);
    void WriteString(const char *sec, const char *key, const std::string &val, const char *comment = nullptr);
    void WriteModelArray(const char *sec, const char *key, const int *array, int count, const char *comment = nullptr);

    bool Exists();
    void Format(const std::string &headerComments = "");

    static int EnumtoNum(const std::string &name);
    static std::string NumtoEnum(int num);
};
