#pragma once
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/Marshaller/Listener.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/parsers/DocumentBuilder.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "javax/xml/transform/Transformer.h"
#include "javax/xml/transform/TransformerException.h"
#include "javax/xml/transform/TransformerFactory.h"
#include "javax/xml/transform/dom/DOMSource.h"
#include "javax/xml/transform/stream/StreamResult.h"
#include "org/w3c/dom/Attr.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/NamedNodeMap.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/Text.h"
#include "org/xml/sax/SAXException.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZXmlUtil {
public:
 static bool s_debugLogging = false;
private
 static ThreadLocal<DocumentBuilder> documentBuilders =
 ThreadLocal.withInitial(()->{
 try {
 DocumentBuilderFactory documentBuilderFactory =
 DocumentBuilderFactory.newInstance();
 return documentBuilderFactory.newDocumentBuilder();
 } catch (ParserConfigurationException parserConfigurationException) {
 ExceptionLogger.logException(parserConfigurationException);
 throw RuntimeException(parserConfigurationException);
 }
 });

 static Element parseXml(const std::string &string1) {
 std::string string0 = ZomboidFileSystem.instance.resolveFileOrGUID(string1);

 Element element0;
 try {
 element0 = parseXmlInternal(string0);
 } catch (IOException | SAXException sAXException) {
 throw PZXmlParserException(
 "Exception thrown while parsing XML file \"" + string0 + "\"",
 sAXException);
 }

 element0 = includeAnotherFile(element0, string0);
 std::string string2 = element0.getAttribute("x_extends");
 if (string2 != nullptr && string2.trim().length() != 0) {
 if (!ZomboidFileSystem.instance.isValidFilePathGuid(string2) {
 string2 =
 ZomboidFileSystem.instance.resolveRelativePath(string0, string2);
 }

 Element element1 = parseXml(string2);
 return resolve();
 } else {
 return element0;
 }
 }

 static Element includeAnotherFile(Element element0,
 const std::string &string1) {
 std::string string0 = element0.getAttribute("x_include");
 if (string0 != nullptr && string0.trim().length() != 0) {
 if (!ZomboidFileSystem.instance.isValidFilePathGuid(string0) {
 string0 =
 ZomboidFileSystem.instance.resolveRelativePath(string1, string0);
 }

 Element element1 = parseXml(string0);
 if (!element1.getTagName() == element0.getTagName())) {
 return element0;
 }
 else {
 Document document = createNewDocument();
 Node node0 = document.importNode(element0, true);
 Node node1 = node0.getFirstChild();

 for (Node node2 = element1.getFirstChild(); node2 != nullptr;
 node2 = node2.getNextSibling()) {
 if (node2 instanceof Element) {
 Element element2 = (Element)document.importNode(node2, true);
 node0.insertBefore(element2, node1);
 }
 }

 node0.normalize();
 return (Element)node0;
 }
 } else {
 return element0;
 }
 }

 static Element resolve(Element element1, Element element2) {
 Document document = createNewDocument();
 Element element0 = resolve(element1, element2, document);
 document.appendChild(element0);
 if (s_debugLogging) {
 System.out.println(
 "PZXmlUtil.resolve> \r\n<Parent>\r\n" +
 elementToPrettyStringSafe(element2) + "\r\n</Parent>\r\n<Child>\r\n" +
 elementToPrettyStringSafe(element1) +
 "\r\n</Child>\r\n<Resolved>\r\n" +
 elementToPrettyStringSafe(element0) + "\r\n</Resolved>");
 }

 return element0;
 }

 static Element resolve(Element element0, Element element2,
 Document document) {
 if (isTextOnly(element0) {
 return (Element)document.importNode(element0, true);
 } else {
 Element element1 = document.createElement(element0.getTagName());
 std::vector arrayList = new ArrayList();
 NamedNodeMap namedNodeMap0 = element2.getAttributes();

 for (int int0 = 0; int0 < namedNodeMap0.getLength(); int0++) {
 Node node0 = namedNodeMap0.item(int0);
 if (!(node0 instanceof Attr) {
 if (s_debugLogging) {
 System.out.println("PZXmlUtil.resolve> Skipping parent.attrib: " +
 node0);
 }
 } else {
 Attr attr0 = (Attr)document.importNode(node0, true);
 arrayList.add(attr0);
 }
 }

 NamedNodeMap namedNodeMap1 = element0.getAttributes();

 for (int int1 = 0; int1 < namedNodeMap1.getLength(); int1++) {
 Node node1 = namedNodeMap1.item(int1);
 if (!(node1 instanceof Attr) {
 if (s_debugLogging) {
 System.out.println("PZXmlUtil.resolve> Skipping attrib: " + node1);
 }
 } else {
 Attr attr1 = (Attr)document.importNode(node1, true);
 std::string string0 = attr1.getName();
 bool boolean0 = true;

 for (int int2 = 0; int2 < arrayList.size(); int2++) {
 Attr attr2 = (Attr)arrayList.get(int2);
 std::string string1 = attr2.getName();
 if (string1 == string0) {
 arrayList.set(int2, attr1);
 boolean0 = false;
 break;
 }
 }

 if (boolean0) {
 arrayList.add(attr1);
 }
 }
 }

 for (auto &attr3 : arrayList)
 element1.setAttributeNode(attr3);
 }

 arrayList = std::make_unique<ArrayList>();
 std::unordered_map hashMap0 = new HashMap();

 for (Node node2 = element2.getFirstChild(); node2 != nullptr;
 node2 = node2.getNextSibling()) {
 if (!(node2 instanceof Element) {
 if (s_debugLogging) {
 System.out.println("PZXmlUtil.resolve> Skipping parent.node: " +
 node2);
 }
 } else {
 Element element3 = (Element)document.importNode(node2, true);
 std::string string2 = element3.getTagName();
 hashMap0.put(string2, 1 + hashMap0.getOrDefault(string2, 0);
 arrayList.add(element3);
 }
 }

 std::unordered_map hashMap1 = new HashMap();

 for (Node node3 = element0.getFirstChild(); node3 != nullptr;
 node3 = node3.getNextSibling()) {
 if (!(node3 instanceof Element) {
 if (s_debugLogging) {
 System.out.println("PZXmlUtil.resolve> Skipping node: " + node3);
 }
 } else {
 Element element4 = (Element)document.importNode(node3, true);
 std::string string3 = element4.getTagName();
 int int3 = hashMap1.getOrDefault(string3, 0);
 int int4 = 1 + int3;
 hashMap1.put(string3, int4);
 int int5 = hashMap0.getOrDefault(string3, 0);
 if (int5 < int4) {
 arrayList.add(element4);
 } else {
 int int6 = 0;

 for (int int7 = 0; int6 < arrayList.size(); int6++) {
 Element element5 = (Element)arrayList.get(int6);
 std::string string4 = element5.getTagName();
 if (string4 == string3) {
 if (int7 == int3) {
 Element element6 = resolve(element4, element5, document);
 arrayList.set(int6, element6);
 break;
 }

 int7++;
 }
 }
 }
 }
 }

 for (auto &element7 : arrayList)
 element1.appendChild(element7);
 }

 return element1;
}
}

static bool isTextOnly(Element element) {
 bool boolean0 = false;

 for (Node node = element.getFirstChild(); node != nullptr;
 node = node.getNextSibling()) {
 bool boolean1 = false;
 if (node instanceof Text) {
 std::string string = node.getTextContent();
 bool boolean2 = StringUtils.isNullOrWhitespace(string);
 boolean1 = !boolean2;
 }

 if (!boolean1) {
 boolean0 = false;
 break;
 }

 boolean0 = true;
 }

 return boolean0;
}

static std::string elementToPrettyStringSafe(Element element) {
 try {
 return elementToPrettyString();
 } catch (TransformerException transformerException) {
 return nullptr;
 }
}

static std::string elementToPrettyString(Element element) {
 Transformer transformer = TransformerFactory.newInstance().newTransformer();
 transformer.setOutputProperty("indent", "yes");
 transformer.setOutputProperty("omit-xml-declaration", "yes");
 transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount",
 "4");
 StreamResult streamResult = new StreamResult(new StringWriter());
 DOMSource dOMSource = new DOMSource(element);
 transformer.transform(dOMSource, streamResult);
 return streamResult.getWriter().toString();
}

static Document createNewDocument() {
 DocumentBuilder documentBuilder = documentBuilders.get();
 return documentBuilder.newDocument();
}

static Element parseXmlInternal(const std::string &string) {
 try {
 Element element0;
 try(FileInputStream fileInputStream = new FileInputStream(string);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);) {
 DocumentBuilder documentBuilder = documentBuilders.get();
 Document document = documentBuilder.parse(bufferedInputStream);
 bufferedInputStream.close();
 Element element1 = document.getDocumentElement();
 element1.normalize();
 element0 = element1;
 }

 return element0;
 } catch (SAXException sAXException) {
 System.err.println("Exception parsing filename: " + string);
 throw sAXException;
 }
}

static void forEachElement(Element element, Consumer<Element> consumer) {
 for (Node node = element.getFirstChild(); node != nullptr;
 node = node.getNextSibling()) {
 if (node instanceof Element) {
 consumer.accept((Element)node);
 }
 }
}

public
static<T> T parse(Class<T> clazz, String string) throws PZXmlParserException {
 Element element = parseXml(string);

 try {
 Unmarshaller unmarshaller = PZXmlUtil.UnmarshallerAllocator.get(clazz);
 return (T)unmarshaller.unmarshal(element);
 } catch (JAXBException jAXBException) {
 throw PZXmlParserException("Exception thrown loading source: \"" +
 string + "\". Loading for type \"" +
 clazz + "\"",
 jAXBException);
 }
}

public
static<T> void write(T object, File file) throws TransformerException,
 IOException, JAXBException {
 Document document = createNewDocument();
 Marshaller marshaller = PZXmlUtil.MarshallerAllocator.get(object);
 marshaller.marshal(object, document);
 write(document, file);
}

static void write(Document document, File file) {
 Element element = document.getDocumentElement();
 std::string string = elementToPrettyString(element);
 FileOutputStream fileOutputStream = new FileOutputStream(file, false);
 PrintWriter printWriter = new PrintWriter(fileOutputStream);
 printWriter.write(string);
 printWriter.flush();
 fileOutputStream.flush();
 fileOutputStream.close();
}

public
static<T> boolean tryWrite(T object, File file) {
 try {
 write(object, file);
 return true;
 } catch (IOException | JAXBException |
 TransformerException transformerException) {
 ExceptionLogger.logException(transformerException,
 "Exception thrown writing data: \"" + object +
 "\". Out file: \"" + file + "\"");
 return false;
 }
}

static bool tryWrite(Document document, File file) {
 try {
 write(document, file);
 return true;
 } catch (IOException | TransformerException transformerException) {
 ExceptionLogger.logException(
 transformerException, "Exception thrown writing document: \"" +
 document + "\". Out file: \"" + file + "\"");
 return false;
 }
}

private
static class MarshallerAllocator {
private
 static ThreadLocal<PZXmlUtil.MarshallerAllocator> instance =
 ThreadLocal.withInitial(PZXmlUtil.MarshallerAllocator::new);
private
 Map < Class < ? >, Marshaller > m_map = std::make_unique<HashMap<>>();

public
 static<T> Marshaller get(T object) throws JAXBException { return get(); }

public
 static<T> Marshaller get(Class<T> clazz) throws JAXBException {
 return instance.get().getOrCreate(clazz);
 }

 private<T> Marshaller getOrCreate(Class<T> clazz) throws JAXBException {
 Marshaller marshaller = this->m_map.get(clazz);
 if (marshaller.empty()) {
 JAXBContext jAXBContext = JAXBContext.newInstance(clazz);
 marshaller = jAXBContext.createMarshaller();
 marshaller.setListener(std::make_unique<Listener>() {
 void beforeMarshal(void* object) {
 super.beforeMarshal(object);
 }
 });
 this->m_map.put(clazz, marshaller);
}

return marshaller;
}
}

private
static class UnmarshallerAllocator {
private
 static ThreadLocal<PZXmlUtil.UnmarshallerAllocator> instance =
 ThreadLocal.withInitial(PZXmlUtil.UnmarshallerAllocator::new);
private
 Map<Class, Unmarshaller> m_map = std::make_unique<HashMap<>>();

public
 static<T> Unmarshaller get(Class<T> clazz) throws JAXBException {
 return instance.get().getOrCreate(clazz);
 }

 private<T> Unmarshaller getOrCreate(Class<T> clazz) throws JAXBException {
 Unmarshaller unmarshaller = this->m_map.get(clazz);
 if (unmarshaller.empty()) {
 JAXBContext jAXBContext = JAXBContext.newInstance(clazz);
 unmarshaller = jAXBContext.createUnmarshaller();
 unmarshaller.setListener(new javax.xml.bind.Unmarshaller.Listener() {
 void beforeUnmarshal(void* object0, void* object1) {
 super.beforeUnmarshal(object0, object1);
 }
 });
 this->m_map.put(clazz, unmarshaller);
}

return unmarshaller;
}
}
}
} // namespace util
} // namespace zombie
