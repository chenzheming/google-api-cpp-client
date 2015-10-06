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

// This code was generated by google-apis-code-generator 1.5.1
//   C++ generator version: 0.1.3

// ----------------------------------------------------------------------------
// NOTE: This file is generated from Google APIs Discovery Service.
// Service:
//   YouTube Data API (youtube/v3)
// Generated from:
//   Version: v3
// Generated by:
//    Tool: google-apis-code-generator 1.5.1
//     C++: 0.1.3
#ifndef  GOOGLE_YOUTUBE_API_VIDEO_SUGGESTIONS_TAG_SUGGESTION_H_
#define  GOOGLE_YOUTUBE_API_VIDEO_SUGGESTIONS_TAG_SUGGESTION_H_

#include <string>
#include "googleapis/base/macros.h"
#include "googleapis/client/data/jsoncpp_data.h"
#include "googleapis/strings/stringpiece.h"

namespace Json {
class Value;
}  // namespace Json

namespace google_youtube_api {
using namespace googleapis;

/**
 * A single tag suggestion with it's relevance information.
 *
 * @ingroup DataObject
 */
class VideoSuggestionsTagSuggestion : public client::JsonCppData {
 public:
  /**
   * Creates a new default instance.
   *
   * @return Ownership is passed back to the caller.
   */
  static VideoSuggestionsTagSuggestion* New();

  /**
   * Standard constructor for an immutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit VideoSuggestionsTagSuggestion(const Json::Value& storage);

  /**
   * Standard constructor for a mutable data object instance.
   *
   * @param[in] storage  The underlying data storage for this instance.
   */
  explicit VideoSuggestionsTagSuggestion(Json::Value* storage);

  /**
   * Standard destructor.
   */
  virtual ~VideoSuggestionsTagSuggestion();

  /**
   * Returns a string denoting the type of this data object.
   *
   * @return <code>google_youtube_api::VideoSuggestionsTagSuggestion</code>
   */
  const StringPiece GetTypeName() const {
    return StringPiece("google_youtube_api::VideoSuggestionsTagSuggestion");
  }

  /**
   * Determine if the '<code>categoryRestricts</code>' attribute was set.
   *
   * @return true if the '<code>categoryRestricts</code>' attribute was set.
   */
  bool has_category_restricts() const {
    return Storage().isMember("categoryRestricts");
  }

  /**
   * Clears the '<code>categoryRestricts</code>' attribute.
   */
  void clear_category_restricts() {
    MutableStorage()->removeMember("categoryRestricts");
  }


  /**
   * Get a reference to the value of the '<code>categoryRestricts</code>'
   * attribute.
   */
  const client::JsonCppArray<string > get_category_restricts() const {
     const Json::Value& storage = Storage("categoryRestricts");
    return client::JsonValueToCppValueHelper<client::JsonCppArray<string > >(storage);
  }

  /**
   * Gets a reference to a mutable value of the '<code>categoryRestricts</code>'
   * property.
   *
   * A set of video categories for which the tag is relevant. You can use this
   * information to display appropriate tag suggestions based on the video
   * category that the video uploader associates with the video. By default, tag
   * suggestions are relevant for all categories if there are no restricts
   * defined for the keyword.
   *
   * @return The result can be modified to change the attribute value.
   */
  client::JsonCppArray<string > mutable_categoryRestricts() {
    Json::Value* storage = MutableStorage("categoryRestricts");
    return client::JsonValueToMutableCppValueHelper<client::JsonCppArray<string > >(storage);
  }

  /**
   * Determine if the '<code>tag</code>' attribute was set.
   *
   * @return true if the '<code>tag</code>' attribute was set.
   */
  bool has_tag() const {
    return Storage().isMember("tag");
  }

  /**
   * Clears the '<code>tag</code>' attribute.
   */
  void clear_tag() {
    MutableStorage()->removeMember("tag");
  }


  /**
   * Get the value of the '<code>tag</code>' attribute.
   */
  const StringPiece get_tag() const {
    const Json::Value& v = Storage("tag");
    if (v == Json::Value::null) return StringPiece("");
    return StringPiece(v.asCString());
  }

  /**
   * Change the '<code>tag</code>' attribute.
   *
   * The keyword tag suggested for the video.
   *
   * @param[in] value The new value.
   */
  void set_tag(const StringPiece& value) {
    *MutableStorage("tag") = value.data();
  }

 private:
  void operator=(const VideoSuggestionsTagSuggestion&);
};  // VideoSuggestionsTagSuggestion
}  // namespace google_youtube_api
#endif  // GOOGLE_YOUTUBE_API_VIDEO_SUGGESTIONS_TAG_SUGGESTION_H_