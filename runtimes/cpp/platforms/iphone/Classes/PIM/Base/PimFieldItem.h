/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

// The attribute is custom.
#define CUSTOM_ATTRIBUTE -1

#import <Foundation/Foundation.h>
#import "PimFieldItemValue.h"

/**
 * Class PimFieldItem.
 * Stores the content of a field. The field is defined by one of
 * the MA_PIM_FIELD_CONTACT constants.
 */
@interface PimFieldItem: NSObject {
    /**
     * Type of the field. Must be one of
     * MA_PIM_TYPE constants.
     */
    int mFieldType;

    /**
     * Must be one of MA_PIM_FIELD_CONTACT constants.
     */
    int mFieldConstant;

    /**
     * Stores the values.
     */
    NSMutableArray* mFieldValuesArray;

    /**
     * True is this field is an single field value(e.g. this field can
     * contain only one value).
     */
    bool mIsSingleFieldValue;
}

/**
 * Init function.
 * @param fieldID Must be one of MA_PIM_FIELD_CONTACT constants.
 * If the fieldID param is invalid or not supported on this platform,
 * the function returns nil.
 */
-(id) initWithFieldID:(int) fieldID;

/**
 * Get field constant.
 * @return One of MA_PIM_FIELD_CONTACT constants.
 */
-(int) getFieldConstant;

/**
 * Get field's type.
 * @return One of MA_PIM_TYPE constants.
 */
-(int) getFieldType;

/**
 * Get the number of values inside this field.
 * @return The number of values inside this field.
 */
-(int) count;

/**
 * Get the attribute of a specified value.
 * @param index The specified index value.
 * @return One of MA_PIM_ATTR constants, or MA_PIM_ERR_INVALID_INDEX
 *         if index param is not valid.
 */
-(int) getAttribute:(int) index;

/**
 * Set a custom label for a value in this field.
 * @param customLabel Label's value.
 * @param index Value's index.
 * @return One of MA_PIM_ERR constants.
 */
-(int) setLabel:(NSString*) customLabel
        atIndex:(int) index;

/**
 * Gets a custom label value for a given field's value.
 * @param value Will contain the custom label value.
 * @param index Value's index.
 * @return One of MA_PIM_ERR constants.
 */
-(int) getLabel:(NSMutableString*) value
     indexValue:(const int) index;

/**
 * Gets the values at a specified index.
 * @param index The specified index.
 * @return An array containing the values, or nil if the index
 *         does not exist.
 */
-(NSMutableArray*) getValue:(const int) index;

/**
 * Set the value and attribute at a specified index.
 * @param value The value.
 * @param index The specified index.
 * @param attribute The specified attribute.
 * @return One of MA_PIM_ERR constants.
 */
-(int) setValue:(NSMutableArray*) value
        atIndex:(int) index
  withAttribute:(int) attribute;

/**
 * Add a value and attribute.
 * @param value The value.
 * @param attribute The specified attribute.
 * @return The new value's index, or one of MA_PIM_ERR constants in
 *         case of error.
 */
-(int) addValue:(NSMutableArray*) value
  withAttribute:(const int) attribute;

/**
 * Add a value and attribute.
 * @param value The value.
 * @param attribute The specified string attribute.
 * @return The new value's index, or one of MA_PIM_ERR constants in
 *         case of error.
 */
-(int) addValue:(NSMutableArray*) value
withLabel:(NSString*) label;

/**
 * Remove the value at a specified index.
 * @param index The specified index.
 * @return One of MA_PIM_ERR constants.
 */
-(int) removeValue:(int) index;

/**
 * Gets and item at a given index.
 * @param index The speicified index.
 * @return The item.
 */
-(PimFieldItemValue*) getItem:(int) index;

/**
 * Checks if an specified attribute is valid.
 * @param attributeID The given attribute.
 * @return True if the attribute is valid, false otherwise.
 */
-(bool) isAttributeValid:(const int) attributeID;

/**
 * Gets the string value for an attribute.
 * @param The given attribute id.
 */
-(NSString*) getStringAttribute:(const int) attributeID;

/**
 * Gets the attribute id from a specifed label value.
 * @param label The given label.
 * @return The attribute id, or CUSTOM_ATTRIBUTE is the attribute is custom.
 */
-(int) getAttributeFromLabel:(NSString*) label;

@end
