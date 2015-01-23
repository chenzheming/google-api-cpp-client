// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

// This code was generated by google-apis-code-generator 1.5.0
//   Build date: 2014-11-17 18:43:33 UTC
//   on: 2014-12-19, 09:55:43 UTC
//   C++ generator version:

// ----------------------------------------------------------------------------
// NOTE: This file is generated from Google APIs Discovery Service.
// Service:
//   Calendar API (calendar/v3)
// Generated from:
//   Version: v3
//   Revision: 111
// Generated by:
//    Tool: google-apis-code-generator 1.5.0
//     C++: 0.1.2
#ifndef  GOOGLE_CALENDAR_API_COLOR_DEFINITION_H_
#define  GOOGLE_CALENDAR_API_COLOR_DEFINITION_H_

#include <string>
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

namespace Json {
class Value;
}  // namespace Json

namespace google_calendar_api {
using namespace googleapis;

/**
 * No description provided.
 *
 * @ingroup DataObject
 */
class ColorDefinition : public client::JsonCppData {
 public:

  /**
   * Creates a new default instance.
   *
   * @return Ownership is passed back to the caller.
   */
  static ColorDefinition* New();

  /**
   * Standard constructor for an immutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit ColorDefinition(const Json::Value& storage);

  /**
   * Standard constructor for a mutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit ColorDefinition(Json::Value* storage);

  /**
   * Standard destructor.
   */
  virtual ~ColorDefinition();

  /**
   * Returns a string denoting the type of this data object.
   *
   * @return <code>google_calendar_api::ColorDefinition</code>
   */
  const StringPiece GetTypeName() const {
    return StringPiece("google_calendar_api::ColorDefinition");
  }

  /**
   * Determine if the '<code>background</code>' attribute was set.
   *
   * @return true if the '<code>background</code>' attribute was set.
   */
  bool has_background() const {
    return Storage().isMember("background");
  }

  /**
   * Clears the '<code>background</code>' attribute.
   */
  void clear_background() {
    MutableStorage()->removeMember("background");
  }


  /**
   * Get the value of the '<code>background</code>' attribute.
   */
  const StringPiece get_background() const {
    const Json::Value& v = Storage("background");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>background</code>' attribute.
   *
   * The background color associated with this color definition.
   *
   * @param[in] value The new value.
   */
  void set_background(const StringPiece& value) {
    *MutableStorage("background") = value.data();
  }

  /**
   * Determine if the '<code>foreground</code>' attribute was set.
   *
   * @return true if the '<code>foreground</code>' attribute was set.
   */
  bool has_foreground() const {
    return Storage().isMember("foreground");
  }

  /**
   * Clears the '<code>foreground</code>' attribute.
   */
  void clear_foreground() {
    MutableStorage()->removeMember("foreground");
  }


  /**
   * Get the value of the '<code>foreground</code>' attribute.
   */
  const StringPiece get_foreground() const {
    const Json::Value& v = Storage("foreground");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>foreground</code>' attribute.
   *
   * The foreground color that can be used to write on top of a background with
   * 'background' color.
   *
   * @param[in] value The new value.
   */
  void set_foreground(const StringPiece& value) {
    *MutableStorage("foreground") = value.data();
  }

 private:
  void operator=(const ColorDefinition&);
};  // ColorDefinition
}  // namespace google_calendar_api
#endif  // GOOGLE_CALENDAR_API_COLOR_DEFINITION_H_
