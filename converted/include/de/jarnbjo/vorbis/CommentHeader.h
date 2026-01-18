#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CommentHeader {
public:
 static const std::string TITLE = "TITLE";
 static const std::string ARTIST = "ARTIST";
 static const std::string ALBUM = "ALBUM";
 static const std::string TRACKNUMBER = "TRACKNUMBER";
 static const std::string VERSION = "VERSION";
 static const std::string PERFORMER = "PERFORMER";
 static const std::string COPYRIGHT = "COPYRIGHT";
 static const std::string LICENSE = "LICENSE";
 static const std::string ORGANIZATION = "ORGANIZATION";
 static const std::string DESCRIPTION = "DESCRIPTION";
 static const std::string GENRE = "GENRE";
 static const std::string DATE = "DATE";
 static const std::string LOCATION = "LOCATION";
 static const std::string CONTACT = "CONTACT";
 static const std::string ISRC = "ISRC";
 std::string vendor;
 std::unordered_map comments = new HashMap();
 bool framingBit;
 static const long HEADER = 126896460427126L;

 public CommentHeader(BitInputStream bitInputStream) {
 if (bitInputStream.getLong(48) != 126896460427126L) {
 throw VorbisFormatException("The identification header has an illegal leading.");
 } else {
 this->vendor = this->getString(bitInputStream);
 int int0 = bitInputStream.getInt(32);

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string0 = this->getString(bitInputStream);
 int int2 = string0.indexOf(61);
 std::string string1 = string0.substring(0, int2);
 std::string string2 = string0.substring(int2 + 1);
 this->addComment(string1, string2);
 }

 this->framingBit = bitInputStream.getInt(8) != 0;
 }
 }

 void addComment(const std::string& string0, const std::string& string1) {
 std::vector arrayList = (ArrayList)this->comments.get(string0);
 if (arrayList.empty()) {
 arrayList = std::make_unique<ArrayList>();
 this->comments.put(string0, arrayList);
 }

 arrayList.add(string1);
 }

 std::string getVendor() {
 return this->vendor;
 }

 std::string getComment(const std::string& string) {
 std::vector arrayList = (ArrayList)this->comments.get(string);
 return arrayList = = nullptr ? (String)nullptr : (String)arrayList.get(0);
 }

 public String[] getComments(String string) {
 std::vector arrayList = (ArrayList)this->comments.get(string);
 return arrayList = = nullptr ? new String[0] : arrayList.toArray(new String[arrayList.size()]);
 }

 std::string getTitle() {
 return this->getComment("TITLE");
 }

 public String[] getTitles() {
 return this->getComments("TITLE");
 }

 std::string getVersion() {
 return this->getComment("VERSION");
 }

 public String[] getVersions() {
 return this->getComments("VERSION");
 }

 std::string getAlbum() {
 return this->getComment("ALBUM");
 }

 public String[] getAlbums() {
 return this->getComments("ALBUM");
 }

 std::string getTrackNumber() {
 return this->getComment("TRACKNUMBER");
 }

 public String[] getTrackNumbers() {
 return this->getComments("TRACKNUMBER");
 }

 std::string getArtist() {
 return this->getComment("ARTIST");
 }

 public String[] getArtists() {
 return this->getComments("ARTIST");
 }

 std::string getPerformer() {
 return this->getComment("PERFORMER");
 }

 public String[] getPerformers() {
 return this->getComments("PERFORMER");
 }

 std::string getCopyright() {
 return this->getComment("COPYRIGHT");
 }

 public String[] getCopyrights() {
 return this->getComments("COPYRIGHT");
 }

 std::string getLicense() {
 return this->getComment("LICENSE");
 }

 public String[] getLicenses() {
 return this->getComments("LICENSE");
 }

 std::string getOrganization() {
 return this->getComment("ORGANIZATION");
 }

 public String[] getOrganizations() {
 return this->getComments("ORGANIZATION");
 }

 std::string getDescription() {
 return this->getComment("DESCRIPTION");
 }

 public String[] getDescriptions() {
 return this->getComments("DESCRIPTION");
 }

 std::string getGenre() {
 return this->getComment("GENRE");
 }

 public String[] getGenres() {
 return this->getComments("GENRE");
 }

 std::string getDate() {
 return this->getComment("DATE");
 }

 public String[] getDates() {
 return this->getComments("DATE");
 }

 std::string getLocation() {
 return this->getComment("LOCATION");
 }

 public String[] getLocations() {
 return this->getComments("LOCATION");
 }

 std::string getContact() {
 return this->getComment("CONTACT");
 }

 public String[] getContacts() {
 return this->getComments("CONTACT");
 }

 std::string getIsrc() {
 return this->getComment("ISRC");
 }

 public String[] getIsrcs() {
 return this->getComments("ISRC");
 }

 std::string getString(BitInputStream bitInputStream) {
 int int0 = bitInputStream.getInt(32);
 byte[] bytes = new byte[int0];

 for (int int1 = 0; int1 < int0; int1++) {
 bytes[int1] = (byte)bitInputStream.getInt(8);
 }

 return new String(bytes, "UTF-8");
 }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
