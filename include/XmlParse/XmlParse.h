#ifndef XMLPARSE_H
#define XMLPARSE_H

#include "XmlParseDataObject.h"

class XmlParse
{
public:
    static XmlParse *getInstance();
    //解析plugins.xml文件
    PluginsInfoObj parsePluginsXml();
private:
    explicit XmlParse();
};

#endif // XMLPARSE_H
