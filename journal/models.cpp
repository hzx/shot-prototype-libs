#include "models.h"


namespace journal {


std::string const Journal::S_NAME = std::to_string(Journal::NAME);
std::string const Journal::S_SLUG = std::to_string(Journal::SLUG);
std::string const Journal::S_KEYWORDS = std::to_string(Journal::KEYWORDS);
std::string const Journal::S_DESCRIPTION = std::to_string(Journal::DESCRIPTION);
std::string const Journal::S_SHOW = std::to_string(Journal::SHOW);
std::string const Journal::S_ITEMS = std::to_string(Journal::ITEMS);
std::string const Journal::S_TAGS = std::to_string(Journal::TAGS);


int Journal::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(S_NAME)) name.set(obj.getField(S_NAME).String());
  if (obj.hasField(S_SLUG)) slug.set(obj.getField(S_SLUG).String());
  if (obj.hasField(S_KEYWORDS)) keywords.set(obj.getField(S_KEYWORDS).String());
  if (obj.hasField(S_DESCRIPTION))
    description.set(obj.getField(S_DESCRIPTION).String());
  if (obj.hasField(S_SHOW)) {
    int val = obj.getField(S_SHOW).Int();
    show.set(val == 1);
  }
  if (obj.hasField(S_ITEMS)) {
    // TODO: fill items
  }
  if (obj.hasField(S_TAGS)) {
    // TODO: split obj.tags and fill tags
  }

  return 0;
}


int Journal::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case NAME:
      name.set(value);
      break;
    case SLUG:
      slug.set(value);
      break;
    case KEYWORDS:
      keywords.set(value);
      break;
    case DESCRIPTION:
      description.set(value);
      break;
    case SHOW:
      show.set(std::stoi(value) == 1);
      break;
    case ITEMS: // TODO: set
      break;
    case TAGS: // TODO: set
      break;
  }

  return 0;
}


void Journal::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (name.has) builder << S_NAME << name.value;
  if (slug.has) builder << S_SLUG << slug.value;
  if (keywords.has) builder << S_KEYWORDS << keywords.value;
  if (description.has) builder << S_DESCRIPTION << description.value;
  if (show.has) {
    builder << S_SHOW << (show.value ? 1 : 0);
  }
  if (not items.empty()) {
    // TODO: set
    // builder << S_ITEMS <<
  }
  if (not tags.empty()) {
    // TODO: set
    // builder << S_TAGS <<
  }
}


void Journal::toCompactFormat(ostream& stream) {
  if (id.has) stream << shot::ID << DF << id.value << DF;
  if (name.has) stream << S_NAME << DF << name.value << DF;
  if (slug.has) stream << S_SLUG << DF << slug.value << DF;
  if (keywords.has) stream << S_KEYWORDS << DF << keywords.value << DF;
  if (description.has) stream << S_DESCRIPTION << DF << description.value << DF;
  if (show.has) {
    stream << S_SHOW << DF << (show.value ? '1' : '0') << DF;
  }
  if (not items.empty()) {
    // TODO: set
  }
  if (not tags.empty()) {
    // TODO: set
  }
}


JournalItems::~JournalItems() {
  for (auto n: nodes) delete n;
}


std::string const Node::S_TYPE = std::to_string(Node::TYPE);
std::string const Node::S_PAGE_ID = std::to_string(Node::PAGE_ID);
std::string const Node::S_STYLE = std::to_string(Node::STYLE);


Block::Block() {
  nodeType = NodeType::Block;
}

Block::~Block() {
}

int Block::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());

  return 0;
}

int Block::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
  }

  return 0;
}

void Block::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
}

void Block::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
}


Header1::Header1() {
  nodeType = NodeType::H1;
}

int Header1::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());

  return 0;
}

int Header1::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
  }

  return 0;
}

void Header1::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
}

void Header1::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
}


std::string const Header2::S_TEXT = std::to_string(Header2::TEXT);


Header2::Header2() {
  nodeType = NodeType::H2;
}

int Header2::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Header2::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Header2::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Header2::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Text::S_TEXT = std::to_string(Text::TEXT);


Text::Text() {
  nodeType = NodeType::Text;
}

int Text::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Text::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Text::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Text::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Code::S_TEXT = std::to_string(Code::TEXT);


Code::Code() {
  nodeType = NodeType::Code;
}

int Code::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Code::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Code::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Code::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Link::S_SRC = std::to_string(Link::SRC);
std::string const Link::S_ALT = std::to_string(Link::ALT);


Link::Link() {
  nodeType = NodeType::Link;
}

int Link::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_SRC)) src.set(obj.getField(S_SRC).String());
  if (obj.hasField(S_ALT)) alt.set(obj.getField(S_ALT).String());

  return 0;
}

int Link::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case SRC:
      src.set(value);
      break;
    case ALT:
      alt.set(value);
      break;
  }

  return 0;
}

void Link::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (src.has) builder << S_SRC << src.value;
  if (alt.has) builder << S_ALT << alt.value;
}

void Link::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (src.has) stream << S_SRC << DF << src.value << DF;
  if (alt.has) stream << S_ALT << DF << alt.value << DF;
}


std::string const Video::S_TEXT = std::to_string(Video::TEXT);


Video::Video() {
  nodeType = NodeType::Video;
}

int Video::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int Video::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void Video::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (text.has) builder << S_TEXT << text.value;
}

void Video::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const GoogleMap::S_ZOOM = std::to_string(GoogleMap::ZOOM);
std::string const GoogleMap::S_LAT = std::to_string(GoogleMap::LAT);
std::string const GoogleMap::S_LNG = std::to_string(GoogleMap::LNG);


GoogleMap::GoogleMap() {
  nodeType = NodeType::GoogleMap;
}

int GoogleMap::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_ZOOM)) zoom.set(obj.getField(S_ZOOM).Int());
  if (obj.hasField(S_LAT)) lat.set(obj.getField(S_LAT).Double());
  if (obj.hasField(S_LNG)) lng.set(obj.getField(S_LNG).Double());

  return 0;
}

int GoogleMap::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case ZOOM:
      zoom.set(std::stoi(value));
      break;
    case LAT:
      lat.set(std::stof(value));
      break;
    case LNG:
      lng.set(std::stof(value));
      break;
  }

  return 0;
}

void GoogleMap::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (zoom.has) builder << S_ZOOM << zoom.value;
  if (lat.has) builder << S_LAT << lat.value;
  if (lng.has) builder << S_LNG << lng.value;
}

void GoogleMap::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (zoom.has) stream << S_ZOOM << DF << zoom.value << DF;
  if (lat.has) stream << S_LAT << DF << lat.value << DF;
  if (lng.has) stream << S_LNG << DF << lng.value << DF;
}


std::string const File::S_FILENAME = std::to_string(File::FILENAME);
std::string const File::S_TEXT = std::to_string(File::TEXT);


File::File() {
  nodeType = NodeType::File;
}

int File::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_FILENAME)) filename.set(obj.getField(S_FILENAME).String());
  if (obj.hasField(S_TEXT)) text.set(obj.getField(S_TEXT).String());

  return 0;
}

int File::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case FILENAME:
      filename.set(value);
      break;
    case TEXT:
      text.set(value);
      break;
  }

  return 0;
}

void File::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (filename.has) builder << S_FILENAME << filename.value;
  if (text.has) builder << S_TEXT << text.value;
}

void File::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (filename.has) stream << S_FILENAME << DF << filename.value << DF;
  if (text.has) stream << S_TEXT << DF << text.value << DF;
}


std::string const Image::S_FILENAME = std::to_string(Image::FILENAME);


Image::Image() {
  nodeType = NodeType::Image;
}

int Image::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_FILENAME)) filename.set(obj.getField(S_FILENAME).String());

  return 0;
}

int Image::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case FILENAME:
      filename.set(value);
      break;
  }

  return 0;
}

void Image::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (filename.has) builder << S_FILENAME << filename.value;
}

void Image::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (filename.has) stream << S_FILENAME << DF << filename.value << DF;
}


std::string const Gallery::S_IMAGES = std::to_string(Gallery::IMAGES);


Gallery::Gallery() {
  nodeType = NodeType::Gallery;
}

int Gallery::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_IMAGES)) {
    // TODO: split by delimiter and assign
  }

  return 0;
}

int Gallery::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case IMAGES:
      // TODO: split by delimiter and assign
      break;
  }

  return 0;
}

void Gallery::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (images.size() > 0) {
    // TODO: join by : and assign
  }
}

void Gallery::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (images.size() > 0) {
    // TODO: join by : and assign
  }
}


std::string const BigSlider::S_IMAGES = std::to_string(BigSlider::IMAGES);


BigSlider::BigSlider() {
  nodeType = NodeType::BigSlider;
}

int BigSlider::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_IMAGES)) {
    // TODO: split by delimiter and assign
  }

  return 0;
}

int BigSlider::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case IMAGES:
      // TODO: split by delimiter and assign
      break;
  }

  return 0;
}

void BigSlider::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (images.size() > 0) {
    // TODO: join by : and assign
  }
}

void BigSlider::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (images.size() > 0) {
    // TODO: join by : and assign
  }
}


std::string const MiniSlider::S_IMAGES = std::to_string(MiniSlider::IMAGES);


MiniSlider::MiniSlider() {
  nodeType = NodeType::MiniSlider;
}

int MiniSlider::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_IMAGES)) {
    // TODO: split by delimiter and assign
  }

  return 0;
}

int MiniSlider::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case IMAGES:
      // TODO: split by delimiter and assign
      break;
  }

  return 0;
}

void MiniSlider::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (images.size() > 0) {
    // TODO: join by : and assign
  }
}

void MiniSlider::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (images.size() > 0) {
    // TODO: join by : and assign
  }
}


std::string const Anchor::S_NAME = std::to_string(Anchor::NAME);


Anchor::Anchor() {
  nodeType = NodeType::Anchor;
}

int Anchor::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());
  if (obj.hasField(S_NAME)) name.set(obj.getField(S_NAME).String());

  return 0;
}

int Anchor::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
    case NAME:
      name.set(value);
      break;
  }

  return 0;
}

void Anchor::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
  if (name.has) builder << S_NAME << name.value;
}

void Anchor::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
  if (name.has) stream << S_NAME << DF << name.value << DF;
}


Break::Break() {
  nodeType = NodeType::Break;
}

int Break::fromDbFormat(bson::bo& obj) {
  if (obj.hasField(shot::S_ID)) id.set(obj.getField(shot::S_ID).OID().toString());
  if (obj.hasField(Node::S_PAGE_ID)) pageId.set(obj.getField(Node::S_PAGE_ID).OID().toString());
  if (obj.hasField(Node::S_STYLE)) style.set(obj.getField(Node::S_STYLE).String());

  return 0;
}

int Break::parseField(int code, std::string const& value) {
  switch (code) {
    case shot::ID:
      id.set(value);
      break;
    case Node::PAGE_ID:
      pageId.set(value);
      break;
    case Node::STYLE:
      style.set(value);
      break;
  }

  return 0;
}

void Break::toDbFormat(bson::bob& builder) {
  if (id.has) builder << shot::S_ID << mongo::OID(id.value);
  if (pageId.has) builder << Node::S_PAGE_ID << mongo::OID(pageId.value);
  if (style.has) builder << Node::S_STYLE << style.value;
}

void Break::toCompactFormat(ostream& stream) {
  stream << Node::S_TYPE << DF << static_cast<int>(nodeType) << DF;
  if (id.has) stream << shot::S_ID << DF << id.value << DF;
  if (pageId.has) stream << Node::S_PAGE_ID << DF << pageId.value << DF;
  if (style.has) stream << Node::S_STYLE << DF << style.value << DF;
}
  
} /* namespace journal */