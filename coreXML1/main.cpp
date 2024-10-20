#include <iostream>
#include "coreXML.h"


coreXMLdoc doc;
coreXMLrootNode rootNode;
coreXMLfilePtr myFile;
coreXMLflag isActive = false;

int main(void)
{
    std::cout << "Returns : " << initXmlHandler(doc, rootNode, myFile, 1.0, UTF_8, isActive) << std::endl;

    // std::cout << "Doc : " << doc;
    // std::cout << "Rootnode : " << rootNode;
    std::string str = "testNode";
    int ret = addSubRootNode(doc, myFile, str, isActive);
    //adding child node
    std::string childstr11 = "child1";
    addChildNode(doc, myFile, str, childstr11, "1", isActive);
    std::string childstr22 = "child2";
    addChildNode(doc, myFile, str, childstr22, "1", isActive);
    std::string childstr33 = "child3";
    addChildNode(doc, myFile, str, childstr33, "0", isActive);
    closeNode(doc, str, myFile);
    
    str = "testNode1";
    ret = addSubRootNode(doc, myFile, str, isActive);
    //adding child node
    std::string childstr111 = "child1";
    addChildNode(doc, myFile, str, childstr111, "1", isActive);
    std::string childstr222 = "child2";
    addChildNode(doc, myFile, str, childstr222, "1", isActive);
    std::string childstr333 = "child3";
    addChildNode(doc, myFile, str, childstr333, "0", isActive);
    closeNode(doc, str, myFile);
    
    
    str = "testNode2";
    ret = addSubRootNode(doc, myFile, str, isActive);

    std::string str1 = "testNode2_";
    ret = addSubRootNode(doc, myFile, str1, isActive);

    std::string str2 = "testNode2__";
    ret = addSubRootNode(doc, myFile, str2, isActive);
    
    //adding child node
    std::string childstr1 = "child1";
    addChildNode(doc, myFile, str2, childstr1, "1", isActive);
    std::string childstr2 = "child2";
    addChildNode(doc, myFile, str2, childstr2, "1", isActive);
    std::string childstr3 = "child3";
    addChildNode(doc, myFile, str2, childstr3, "0", isActive);
    
    
    closeNode(doc, str2, myFile);


    closeNode(doc, str1, myFile);
    closeNode(doc, str, myFile);



    std::string str7 = "testNodeMain";
    ret = addSubRootNode(doc, myFile, str7, isActive);
    

    std::string str8 = "testNodeMain1";
    ret = addSubRootNode(doc, myFile, str8, isActive);
    closeNode(doc, str8, myFile);
    
    std::string str9 = "testNodeMain2";
    ret = addSubRootNode(doc, myFile, str9, isActive);
    closeNode(doc, str9, myFile);
    
    std::string str10 = "testNodeMain3";
    ret = addSubRootNode(doc, myFile, str10, isActive);
    closeNode(doc, str10, myFile);



    closeNode(doc, str7, myFile);


    saveXmlFile(myFile, rootNode, isActive);

}