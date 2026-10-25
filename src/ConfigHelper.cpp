#include "../includes/ConfigHelper.h"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>

static const ModelEnumMapping modelMappings[] = {
    {"PLAYER", MODEL_PLAYER},
    {"COP", MODEL_COP},
    {"SWAT", MODEL_SWAT},
    {"FBI", MODEL_FBI},
    {"ARMY", MODEL_ARMY},
    {"MEDIC", MODEL_MEDIC},
    {"FIREMAN", MODEL_FIREMAN},
    {"MALE01", MODEL_MALE01},
    {"TAXI_D", MODEL_TAXI_D},
    {"PIMP", MODEL_PIMP},
    {"GANG01", MODEL_GANG01},
    {"GANG02", MODEL_GANG02},
    {"GANG03", MODEL_GANG03},
    {"GANG04", MODEL_GANG04},
    {"GANG05", MODEL_GANG05},
    {"GANG06", MODEL_GANG06},
    {"GANG07", MODEL_GANG07},
    {"GANG08", MODEL_GANG08},
    {"GANG09", MODEL_GANG09},
    {"GANG10", MODEL_GANG10},
    {"GANG11", MODEL_GANG11},
    {"GANG12", MODEL_GANG12},
    {"GANG13", MODEL_GANG13},
    {"GANG14", MODEL_GANG14},
    {"CRIMINAL01", MODEL_CRIMINAL01},
    {"CRIMINAL02", MODEL_CRIMINAL02},
    {"SPECIAL01", MODEL_SPECIAL01},
    {"SPECIAL02", MODEL_SPECIAL02},
    {"SPECIAL03", MODEL_SPECIAL03},
    {"SPECIAL04", MODEL_SPECIAL04},
    {"MALE02", MODEL_MALE02},
    {"MALE03", MODEL_MALE03},
    {"FATMALE01", MODEL_FATMALE01},
    {"FATMALE02", MODEL_FATMALE02},
    {"FEMALE01", MODEL_FEMALE01},
    {"FEMALE02", MODEL_FEMALE02},
    {"FEMALE03", MODEL_FEMALE03},
    {"FATFEMALE01", MODEL_FATFEMALE01},
    {"FATFEMALE02", MODEL_FATFEMALE02},
    {"PROSTITUTE", MODEL_PROSTITUTE},
    {"PROSTITUTE2", MODEL_PROSTITUTE2},
    {"P_MAN1", MODEL_P_MAN1},
    {"P_MAN2", MODEL_P_MAN2},
    {"P_WOM1", MODEL_P_WOM1},
    {"P_WOM2", MODEL_P_WOM2},
    {"CT_MAN1", MODEL_CT_MAN1},
    {"CT_MAN2", MODEL_CT_MAN2},
    {"CT_WOM1", MODEL_CT_WOM1},
    {"CT_WOM2", MODEL_CT_WOM2},
    {"LI_MAN1", MODEL_LI_MAN1},
    {"LI_MAN2", MODEL_LI_MAN2},
    {"LI_WOM1", MODEL_LI_WOM1},
    {"LI_WOM2", MODEL_LI_WOM2},
    {"DOCKER1", MODEL_DOCKER1},
    {"DOCKER2", MODEL_DOCKER2},
    {"SCUM_MAN", MODEL_SCUM_MAN},
    {"SCUM_WOM", MODEL_SCUM_WOM},
    {"WORKER1", MODEL_WORKER1},
    {"WORKER2", MODEL_WORKER2},
    {"B_MAN1", MODEL_B_MAN1},
    {"B_MAN2", MODEL_B_MAN2},
    {"B_MAN3", MODEL_B_MAN3},
    {"B_WOM1", MODEL_B_WOM1},
    {"B_WOM2", MODEL_B_WOM2},
    {"B_WOM3", MODEL_B_WOM3},
    {"MOD_MAN", MODEL_MOD_MAN},
    {"MOD_WOM", MODEL_MOD_WOM},
    {"ST_MAN", MODEL_ST_MAN},
    {"ST_WOM", MODEL_ST_WOM},
    {"FAN_MAN1", MODEL_FAN_MAN1},
    {"FAN_MAN2", MODEL_FAN_MAN2},
    {"FAN_WOM", MODEL_FAN_WOM},
    {"HOS_MAN", MODEL_HOS_MAN},
    {"HOS_WOM", MODEL_HOS_WOM},
    {"CONST1", MODEL_CONST1},
    {"CONST2", MODEL_CONST2},
    {"SHOPPER1", MODEL_SHOPPER1},
    {"SHOPPER2", MODEL_SHOPPER2},
    {"SHOPPER3", MODEL_SHOPPER3},
    {"STUD_MAN", MODEL_STUD_MAN},
    {"STUD_WOM", MODEL_STUD_WOM},
    {"CAS_MAN", MODEL_CAS_MAN},
    {"CAS_WOM", MODEL_CAS_WOM},
    {"BUSKER1", MODEL_BUSKER1},
    {"BUSKER2", MODEL_BUSKER2},
    {"BUSKER3", MODEL_BUSKER3},
    {"BUSKER4", MODEL_BUSKER4},
    {"LANDSTAL", MODEL_LANDSTAL},
    {"IDAHO", MODEL_IDAHO},
    {"STINGER", MODEL_STINGER},
    {"LINERUN", MODEL_LINERUN},
    {"PEREN", MODEL_PEREN},
    {"SENTINEL", MODEL_SENTINEL},
    {"PATRIOT", MODEL_PATRIOT},
    {"FIRETRUCK", MODEL_FIRETRUCK},
    {"TRASH", MODEL_TRASH},
    {"STRETCH", MODEL_STRETCH},
    {"MANANA", MODEL_MANANA},
    {"INFERNUS", MODEL_INFERNUS},
    {"BLISTA", MODEL_BLISTA},
    {"PONY", MODEL_PONY},
    {"MULE", MODEL_MULE},
    {"CHEETAH", MODEL_CHEETAH},
    {"AMBULAN", MODEL_AMBULAN},
    {"FBICAR", MODEL_FBICAR},
    {"MOONBEAM", MODEL_MOONBEAM},
    {"ESPERANT", MODEL_ESPERANT},
    {"TAXI", MODEL_TAXI},
    {"KURUMA", MODEL_KURUMA},
    {"BOBCAT", MODEL_BOBCAT},
    {"MRWHOOP", MODEL_MRWHOOP},
    {"BFINJECT", MODEL_BFINJECT},
    {"CORPSE", MODEL_CORPSE},
    {"POLICE", MODEL_POLICE},
    {"ENFORCER", MODEL_ENFORCER},
    {"SECURICA", MODEL_SECURICA},
    {"BANSHEE", MODEL_BANSHEE},
    {"PREDATOR", MODEL_PREDATOR},
    {"BUS", MODEL_BUS},
    {"RHINO", MODEL_RHINO},
    {"BARRACKS", MODEL_BARRACKS},
    {"TRAIN", MODEL_TRAIN},
    {"CHOPPER", MODEL_CHOPPER},
    {"DODO", MODEL_DODO},
    {"COACH", MODEL_COACH},
    {"CABBIE", MODEL_CABBIE},
    {"STALLION", MODEL_STALLION},
    {"RUMPO", MODEL_RUMPO},
    {"RCBANDIT", MODEL_RCBANDIT},
    {"BELLYUP", MODEL_BELLYUP},
    {"MRWONGS", MODEL_MRWONGS},
    {"MAFIA", MODEL_MAFIA},
    {"YARDIE", MODEL_YARDIE},
    {"YAKUZA", MODEL_YAKUZA},
    {"DIABLOS", MODEL_DIABLOS},
    {"COLUMB", MODEL_COLUMB},
    {"HOODS", MODEL_HOODS},
    {"AIRTRAIN", MODEL_AIRTRAIN},
    {"DEADDODO", MODEL_DEADDODO},
    {"SPEEDER", MODEL_SPEEDER},
    {"REEFER", MODEL_REEFER},
    {"PANLANT", MODEL_PANLANT},
    {"FLATBED", MODEL_FLATBED},
    {"YANKEE", MODEL_YANKEE},
    {"ESCAPE", MODEL_ESCAPE},
    {"BORGNINE", MODEL_BORGNINE},
    {"TOYZ", MODEL_TOYZ},
    {"GHOST", MODEL_GHOST},
    {"GRENADE", MODEL_GRENADE},
    {"AK47", MODEL_AK47},
    {"BASEBALL_BAT", MODEL_BASEBALL_BAT},
    {"COLT", MODEL_COLT},
    {"MOLOTOV", MODEL_MOLOTOV},
    {"ROCKETLAUNCHER", MODEL_ROCKETLAUNCHER},
    {"SHOTGUN", MODEL_SHOTGUN},
    {"SNIPER", MODEL_SNIPER},
    {"UZI", MODEL_UZI},
    {"MISSILE", MODEL_MISSILE},
    {"M16", MODEL_M16},
    {"FLAMETHROWER", MODEL_FLAMETHROWER},
    {"BOMB", MODEL_BOMB},
    {"FINGERS", MODEL_FINGERS},
    {"CUTOBJ01", MODEL_CUTOBJ01},
    {"CUTOBJ02", MODEL_CUTOBJ02},
    {"CUTOBJ03", MODEL_CUTOBJ03},
    {"CUTOBJ04", MODEL_CUTOBJ04},
    {"CUTOBJ05", MODEL_CUTOBJ05},
    {"CAR_DOOR", MODEL_CAR_DOOR},
    {"CAR_BUMPER", MODEL_CAR_BUMPER},
    {"CAR_PANEL", MODEL_CAR_PANEL},
    {"CAR_BONNET", MODEL_CAR_BONNET},
    {"CAR_BOOT", MODEL_CAR_BOOT},
    {"CAR_WHEEL", MODEL_CAR_WHEEL},
    {"BODYPARTA", MODEL_BODYPARTA},
    {"BODYPARTB", MODEL_BODYPARTB},
    {"AIRTRAIN_VLO", MODEL_AIRTRAIN_VLO},
    {"LOPOLYGUY", MODEL_LOPOLYGUY}
};

static const int mappingCount = sizeof(modelMappings) / sizeof(modelMappings[0]);

ConfigHelper::ConfigHelper(const std::string &iniPath) : path(iniPath) {}

bool ConfigHelper::Exists() {
    DWORD attr;

    attr = GetFileAttributesA(path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

void ConfigHelper::StoreComment(const char *sec, const char *key, const char *comment) {
    std::string mapKey;

    if (!comment || comment[0] == '\0') {
        return;
    }
    mapKey = std::string(sec) + "|" + key;
    m_comments[mapKey] = comment;
}

int ConfigHelper::ReadInt(const char *sec, const char *key, int def) {
    return GetPrivateProfileIntA(sec, key, def, path.c_str());
}

std::string ConfigHelper::ReadString(const char *sec, const char *key, const std::string &def) {
    char buf[512];
    size_t hashPos;
    std::string s;

    if (GetPrivateProfileStringA(sec, key, def.c_str(), buf, sizeof(buf), path.c_str()) > 0) {
        s = buf;
        hashPos = s.find('#');
        if (hashPos != std::string::npos) {
            s = s.substr(0, hashPos);
            while (!s.empty() && isspace((unsigned char)s.back())) {
                s.pop_back();
            }
        }
        return s;
    }
    return def;
}

void ConfigHelper::WriteInt(const char *sec, const char *key, int val, const char *comment) {
    char buf[64];

    StoreComment(sec, key, comment);
    sprintf_s(buf, "%d", val);
    WritePrivateProfileStringA(sec, key, buf, path.c_str());
}

void ConfigHelper::WriteString(const char *sec, const char *key, const std::string &val, const char *comment) {
    StoreComment(sec, key, comment);
    WritePrivateProfileStringA(sec, key, val.c_str(), path.c_str());
}

int ConfigHelper::ReadModelArray(const char *sec, const char *key, int *outArray, int maxCount, const int *defaultArray) {
    int i, count, modelId;
    size_t start, commaPos;
    std::string line, token;

    if (defaultArray && outArray != defaultArray) {
        for (i = 0; i < maxCount; i++) {
            outArray[i] = defaultArray[i];
        }
    }

    line = ReadString(sec, key, "");
    if (line.empty()) {
        return 0;
    }

    start = 0;
    count = 0;
    while (start < line.length() && count < maxCount) {
        commaPos = line.find(',', start);
        if (commaPos == std::string::npos) {
            token = line.substr(start);
            start = line.length();
        } else {
            token = line.substr(start, commaPos - start);
            start = commaPos + 1;
        }

        modelId = EnumtoNum(token);
        if (modelId != -1) {
            outArray[count] = modelId;
            count++;
        }
    }

    for (i = count; i < maxCount; i++) {
        outArray[i] = -1;
    }

    return count;
}

void ConfigHelper::WriteModelArray(const char *sec, const char *key, const int *array, int count, const char *comment) {
    int i;
    std::string line;

    line = "";
    for (i = 0; i < count; i++) {
        if (array[i] == -1) {
            continue;
        }
        if (!line.empty()) {
            line += ", ";
        }
        line += NumtoEnum(array[i]);
    }

    WriteString(sec, key, line, comment);
}

int ConfigHelper::EnumtoNum(const std::string &name) {
    int i, parsed, modelId;
    size_t start, end;
    char *endPtr;
    std::string s, stripped;

    start = name.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return -1;
    }
    end = name.find_last_not_of(" \t\r\n");
    s = name.substr(start, end - start + 1);

    for (i = 0; i < (int)s.length(); i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }

    if (s.rfind("MODEL_", 0) == 0) {
        stripped = s.substr(6);
    } else if (s.rfind("MI_", 0) == 0) {
        stripped = s.substr(3);
    } else {
        stripped = s;
    }

    for (i = 0; i < mappingCount; i++) {
        if (stripped == modelMappings[i].name) {
            return modelMappings[i].id;
        }
    }

    parsed = (int)strtol(s.c_str(), &endPtr, 0);
    if (endPtr != s.c_str() && *endPtr == '\0') {
        return parsed;
    }

    return -1;
}

std::string ConfigHelper::NumtoEnum(int num) {
    int i;
    char buf[32];

    for (i = 0; i < mappingCount; i++) {
        if (modelMappings[i].id == num) {
            return "MODEL_" + std::string(modelMappings[i].name);
        }
    }

    sprintf_s(buf, "%d", num);
    return std::string(buf);
}

void ConfigHelper::Format(const std::string &headerComments) {
    FILE *f;
    bool firstSection;
    char line[512];
    size_t eqPos, end;
    std::string content, l, currentSection, mapKey, keyName;
    std::map<std::string, std::string>::iterator it;

    f = nullptr;
    fopen_s(&f, path.c_str(), "r");
    if (!f) {
        return;
    }

    content = "";
    if (!headerComments.empty()) {
        content += headerComments;
        if (headerComments.back() != '\n') {
            content += "\n";
        }
    }

    firstSection = true;
    while (fgets(line, sizeof(line), f)) {
        l = line;
        if (l[0] == ';' || l[0] == '#') {
            continue;
        }
        if (l[0] == '[') {
            if (!firstSection) {
                content += "\n";
            }
            firstSection = false;
            end = l.find(']');
            if (end != std::string::npos) {
                currentSection = l.substr(1, end - 1);
            }
            content += l;
            continue;
        }

        eqPos = l.find('=');
        if (eqPos != std::string::npos && !currentSection.empty()) {
            keyName = l.substr(0, eqPos);
            while (!keyName.empty() && isspace((unsigned char)keyName.back())) {
                keyName.pop_back();
            }
            mapKey = currentSection + "|" + keyName;
            it = m_comments.find(mapKey);
            if (it != m_comments.end() && !it->second.empty()) {
                content += "; " + it->second + "\n";
            }
        }
        content += l;
    }
    fclose(f);

    f = nullptr;
    fopen_s(&f, path.c_str(), "w");
    if (f) {
        fputs(content.c_str(), f);
        fclose(f);
    }
}
