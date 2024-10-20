#pragma once
#include <iostream> 
#include <string>
#include <memory> //for smart pointers
#include <sstream> // for std::stringstream
#include <iomanip> // for std::precision and std::fixed
#include <cstring> // for strstr



#define UTF_8 "UTF-8"
#define UTF_16 "UTF-16"


//typdefs for doc and rootNode
typedef std::string coreXMLdoc; // It will be points to filie(.xml)
typedef std::string coreXMLrootNode; // It will points to root node <root>
typedef FILE* coreXMLfilePtr;

//to point at latest child node and subroot node 
typedef std::shared_ptr<std::string> currentSubRootNode;
typedef std::shared_ptr<std::string> currentChildRootNode;
static bool firstChild = true;

//typdef to check wheather files is still open or not
typedef bool coreXMLflag;
/**
 * @brief TO initialize the XML like setting doc and root node and as well versioning for XML document
 * 
 * \param doc It is doc pointer which will points to fileName
 * \param rootNode This will be main root node for XML document
 * \param p_Ofile This is pointer to store data in opened file
 * \param version To store version for XML document
 * \param utfType Pass flags UTF_8 or UTF_16
 * \param isActive This indicate wheather XML operations are active or not
 * 
 * \result it will return 0 on success and 1 on failure
 */
int initXmlHandler(coreXMLdoc& doc, coreXMLrootNode& rootNode, coreXMLfilePtr& p_Ofile, double version, std::string utfType, coreXMLflag& isActive);
//TODO(initXmlHandler): if required in app itself we will pass file name and main root node name if required

/**
 * @brief To save the xml document
 * 
 * \param p_Ofile This is pointer to store data in opened file
 * \param rootNode This will be main root node for XML document
 * \param isActive This indicate wheather XML operations are active or not
 * 
 */
void saveXmlFile(coreXMLfilePtr& p_Ofile, coreXMLrootNode& rootNode, coreXMLflag& isActive);

/**
 * @brief To add sub root node
 * 
 * \param doc It is doc pointer which will points to fileName
 * \param p_Ofile This is pointer to store data in opened file
 * \param nodeName To store sub root node name
 * \param isActive This indicate wheather XML operations are active or not
 *
 * \result it will return 0 on success and 1 on failure
 */
int addSubRootNode(coreXMLdoc& doc, coreXMLfilePtr& p_Ofile, std::string& nodeName, coreXMLflag& isActive);

/**
 * @brief To close sub root node tag
 * 
 * \param nodeName Indicate which node we have to close
 * \param p_Ofile This is pointer to store data in opened file
 * 
 */
void closeNode(coreXMLdoc& doc, std::string& nodeName, coreXMLfilePtr& p_Ofile);

/**
 * @brief To add child node
 * 
 * \param doc It is doc pointer which will points to fileName
 * \param p_Ofile This is pointer to store data in opened file
 * \param rootNode This will be sub root node for XML document
 * \param nodeName To store child node name
 * \param value Data to store in child nodes
 * \param isActive This indicate wheather XML operations are active or not
 *
 * \result it will return 0 on success and 1 on failure
 */
int addChildNode(coreXMLdoc& doc, coreXMLfilePtr& p_Ofile, std::string& rootNode, std::string& nodeName, std::string value, coreXMLflag& isActive);
