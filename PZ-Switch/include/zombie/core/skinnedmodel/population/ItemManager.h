#pragma once
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Marshaller.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Rand.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ItemManager {
public:
public
 ArrayList<CarriedItem> m_Items = std::make_unique<ArrayList<>>();
 static ItemManager instance;

 static void init() {
 File file = ZomboidFileSystem.instance.getMediaFile(
 "items" + File.separator + "items.xml");
 instance = Parse(file.getPath());
 }

 CarriedItem GetRandomItem() {
 int int0 = Rand.Next(this->m_Items.size() + 1);
 return int0 < this->m_Items.size() ? this->m_Items.get(int0) : nullptr;
 }

 static ItemManager Parse(std::string_view string) {
 try {
 return parse();
 } catch (JAXBException jAXBException) {
 jAXBException.printStackTrace();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 return nullptr;
 }

 static ItemManager parse(std::string_view string) {
 ItemManager itemManager0;
 try(FileInputStream fileInputStream = new FileInputStream(string) {
 JAXBContext jAXBContext = JAXBContext.newInstance(ItemManager.class);
 Unmarshaller unmarshaller = jAXBContext.createUnmarshaller();
 ItemManager itemManager1 =
 (ItemManager)unmarshaller.unmarshal(fileInputStream);
 itemManager0 = itemManager1;
 }

 return itemManager0;
 }

 static void Write(ItemManager itemManager, std::string_view string) {
 try {
 write(itemManager, string);
 } catch (JAXBException jAXBException) {
 jAXBException.printStackTrace();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 static void write(ItemManager itemManager, std::string_view string) {
 try(FileOutputStream fileOutputStream = new FileOutputStream(string) {
 JAXBContext jAXBContext = JAXBContext.newInstance(ItemManager.class);
 Marshaller marshaller = jAXBContext.createMarshaller();
 marshaller.setProperty("jaxb.formatted.output", Boolean.TRUE);
 marshaller.marshal(itemManager, fileOutputStream);
 }
 }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
