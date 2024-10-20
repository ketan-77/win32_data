//This include implementation part
#include "coreXML.h"
//global variables    
currentSubRootNode curSubRootNode = std::make_shared<std::string>("<tfcmConfigurations>"); 
currentChildRootNode curChildRootNode = std::make_shared<std::string>(""); 

int initXmlHandler(coreXMLdoc& doc, coreXMLrootNode& rootNode,coreXMLfilePtr& p_Ofile, double version, std::string utfType, coreXMLflag& isActive)
{
    //TODO: if file already exist remove it start with new
    remove("output.xml");
    
    //init variable
    std::stringstream ss;
    isActive =  true;
    doc = "output.xml";
    rootNode = "tfcmConfigurations";
 
    //open/create file
    p_Ofile = fopen(doc.c_str(), "a+");
    
    if (!p_Ofile){
        std::cerr << "Failed to create file : " << doc << "\n";
        return 1;
    }
    
    ss << "<?xml version=\"" << std::fixed << std::setprecision(1) << version << "\" encoding=\"" << utfType << "\"?>\n";
    fputs(ss.str().c_str(), p_Ofile);
    ss.str("");
    
    ss << "<" << rootNode << ">";
    fputs(ss.str().c_str(), p_Ofile);
    fclose(p_Ofile);
    return 0;
}

void saveXmlFile(coreXMLfilePtr& p_Ofile, coreXMLrootNode& rootNode, coreXMLflag& isActive)
{   
    if(isActive)
    {
        p_Ofile = fopen("output.xml", "a");
        std::stringstream ss;
        ss << "\n</" << rootNode << ">";
        fputs(ss.str().c_str(), p_Ofile);
        fclose(p_Ofile);
    }
    isActive = false;
}

int addSubRootNode(coreXMLdoc& doc, coreXMLfilePtr& p_Ofile, std::string& nodeName, coreXMLflag& isActive)
{
    bool findTag = false;
    p_Ofile = fopen(doc.c_str(), "r");
    FILE* tempFile = fopen("temp.xml", "w");
    if (!tempFile)
    {
        std::cerr << "Failed to get pointer for tempFile\n";
        return 1;
    }

    char line[256]; 
    std::string root = *curSubRootNode;
    // std::cout << "\n new subroot node : " << root << std::endl;
    if(isActive)
    {
        std::stringstream ss; 
        ss << "\n\t<" << nodeName << ">";
        while (fgets(line, sizeof(line), p_Ofile))
        {
            fputs(line, tempFile);
            if (strstr(root.c_str(), line) && !findTag){
                // if(strstr(root.c_str(), "<testNode2>"))
                fputs(ss.str().c_str(), tempFile);
                findTag = true;
            }
            // std::cout << "line : " << line << std::endl;
        }
        // ss.str("");
        // ss << "\n\t<" << nodeName << ">";
        *curSubRootNode = ss.str();
        
        fclose(tempFile);
        fclose(p_Ofile);

        remove(doc.c_str());
        rename("temp.xml", doc.c_str());
        return 0;
    }
    else
    {
        return 1;
    }
}

int addChildNode(coreXMLdoc& doc, coreXMLfilePtr& p_Ofile, std::string& rootNode, std::string& nodeName, std::string value, coreXMLflag& isActive)
{
    bool findTag = false;
    p_Ofile = fopen(doc.c_str(), "r");
    FILE* tempFile = fopen("temp.xml", "w");
    char line[256];
    if (!tempFile)
    {
        std::cerr << "Failed to get pointer for tempFile\n";
        return 1;
    }

    if (firstChild){
        std::cout << "inside 1st child\n";
        *curChildRootNode = "\n\t<" + rootNode + ">";
        firstChild = false;
    }
    
    std::string root = *curChildRootNode;   
    std::cout << "child node " << root << std::endl;

    if(isActive)
    {
        std::stringstream ss;
        ss << "\n\t\t<" << nodeName << ">" << value << "</" << nodeName << ">";
        while (fgets(line, sizeof(line), p_Ofile))
        {
            fputs(line, tempFile);
            if (strstr(root.c_str(), line) && !findTag){

                // if(strstr(root.c_str(), "<testNode2>"))
                fputs(ss.str().c_str(), tempFile);
                findTag = true;
            }
            // std::cout << "line : " << line << std::endl;
        }

        *curChildRootNode = ss.str();

        fclose(tempFile);
        fclose(p_Ofile);

        remove(doc.c_str());
        rename("temp.xml", doc.c_str());
        return 0;
    }
    else
    {
        return 1;
    }

}

void closeNode(coreXMLdoc& doc, std::string& nodeName, coreXMLfilePtr& p_Ofile)
{
    p_Ofile = fopen(doc.c_str(), "a");
    std::stringstream ss;
    ss << "\n\t</" << nodeName << ">";
    *curSubRootNode = ss.str();
    fputs(ss.str().c_str(), p_Ofile);
    fclose(p_Ofile);
    firstChild = true;
}
