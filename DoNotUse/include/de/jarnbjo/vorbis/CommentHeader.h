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
    std::unordered_map comments = new std::unordered_map();
    bool framingBit;
    static const long HEADER = 126896460427126L;

    public CommentHeader(BitInputStream var1) {
      if (var1.getLong(48) != 126896460427126L) {
         throw VorbisFormatException("The identification header has an illegal leading.");
      } else {
         this.vendor = this.getString(var1);
    int var2 = var1.getInt(32);

         for (int var3 = 0; var3 < var2; var3++) {
    std::string var4 = this.getString(var1);
    int var5 = var4.indexOf(61);
    std::string var6 = var4.substr(0, var5);
    std::string var7 = var4.substr(var5 + 1);
            this.addComment(var6, var7);
         }

         this.framingBit = var1.getInt(8) != 0;
      }
   }

    void addComment(const std::string& var1, const std::string& var2) {
    std::vector var3 = (std::vector)this.comments.get(var1);
      if (var3 == nullptr) {
         var3 = std::make_unique<std::vector>();
         this.comments.put(var1, var3);
      }

      var3.push_back(var2);
   }

    std::string getVendor() {
      return this.vendor;
   }

    std::string getComment(const std::string& var1) {
    std::vector var2 = (std::vector)this.comments.get(var1);
    return var2 = = nullptr ? (std::string)nullptr : (std::string)var2.get(0);
   }

   public std::string[] getComments(std::string var1) {
    std::vector var2 = (std::vector)this.comments.get(var1);
    return var2 = = nullptr ? new std::string[0] : var2.toArray(new std::string[var2.size()]);
   }

    std::string getTitle() {
      return this.getComment("TITLE");
   }

   public std::string[] getTitles() {
      return this.getComments("TITLE");
   }

    std::string getVersion() {
      return this.getComment("VERSION");
   }

   public std::string[] getVersions() {
      return this.getComments("VERSION");
   }

    std::string getAlbum() {
      return this.getComment("ALBUM");
   }

   public std::string[] getAlbums() {
      return this.getComments("ALBUM");
   }

    std::string getTrackNumber() {
      return this.getComment("TRACKNUMBER");
   }

   public std::string[] getTrackNumbers() {
      return this.getComments("TRACKNUMBER");
   }

    std::string getArtist() {
      return this.getComment("ARTIST");
   }

   public std::string[] getArtists() {
      return this.getComments("ARTIST");
   }

    std::string getPerformer() {
      return this.getComment("PERFORMER");
   }

   public std::string[] getPerformers() {
      return this.getComments("PERFORMER");
   }

    std::string getCopyright() {
      return this.getComment("COPYRIGHT");
   }

   public std::string[] getCopyrights() {
      return this.getComments("COPYRIGHT");
   }

    std::string getLicense() {
      return this.getComment("LICENSE");
   }

   public std::string[] getLicenses() {
      return this.getComments("LICENSE");
   }

    std::string getOrganization() {
      return this.getComment("ORGANIZATION");
   }

   public std::string[] getOrganizations() {
      return this.getComments("ORGANIZATION");
   }

    std::string getDescription() {
      return this.getComment("DESCRIPTION");
   }

   public std::string[] getDescriptions() {
      return this.getComments("DESCRIPTION");
   }

    std::string getGenre() {
      return this.getComment("GENRE");
   }

   public std::string[] getGenres() {
      return this.getComments("GENRE");
   }

    std::string getDate() {
      return this.getComment("DATE");
   }

   public std::string[] getDates() {
      return this.getComments("DATE");
   }

    std::string getLocation() {
      return this.getComment("LOCATION");
   }

   public std::string[] getLocations() {
      return this.getComments("LOCATION");
   }

    std::string getContact() {
      return this.getComment("CONTACT");
   }

   public std::string[] getContacts() {
      return this.getComments("CONTACT");
   }

    std::string getIsrc() {
      return this.getComment("ISRC");
   }

   public std::string[] getIsrcs() {
      return this.getComments("ISRC");
   }

    std::string getString(BitInputStream var1) {
    int var2 = var1.getInt(32);
      byte[] var3 = new byte[var2];

      for (int var4 = 0; var4 < var2; var4++) {
         var3[var4] = (byte)var1.getInt(8);
      }

      return new std::string(var3, "UTF-8");
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
