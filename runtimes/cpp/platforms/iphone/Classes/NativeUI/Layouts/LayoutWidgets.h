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

#import <Foundation/Foundation.h>

#import "IWidget.h"
#import "AbstractLayoutView.h"
#import "WidgetLayoutingMacro.h"

@interface AbstractLayoutView (AbstractLayoutViewExpanded)
- (void) setVerticalAlignment: (UIControlContentVerticalAlignment) va;
- (void) setHorizontalAlignment: (UIControlContentHorizontalAlignment) ha;
- (void) setSpacing:(int)_spacing;
- (void) setLeftMargin:(int)_margin;
- (void) setRightMargin:(int)_margin;
- (void) setTopMargin:(int)_margin;
- (void) setBottomMargin:(int)_margin;

- (int)getLeftMargin;
- (int)getRightMargin;
- (int)getTopMargin;
- (int)getBottomMargin;
- (int)getSpacing;
@end


typedef enum {
	OrientationVertical,
	OrientationHorizontal
} LinearLayoutOrientation;

@interface LinearLayoutBase : IWidget
{
    /**
     * Layout's orientation.
     */
	LinearLayoutOrientation _orientation;
}

/**
 * Init function.
 * @param orientation Layout's orientation.
 */
-(id)init:(LinearLayoutOrientation)orientation;

/**
 * Adds an widget to the end of the children list.
 * @param child Widget to be added.
 * @return MAW_RES_OK.
 */
-(int)addChild:(IWidget*)child;

/**
 * Insert a widget to a given index.
 * @param child Widget to be added.
 * @param index The index where the child should be inserted.
 * @return MAW_RES_OK if the child was added, MAW_RES_INVALID_INDEX if the index param
 * was invalid.
 */
- (int)insertChild:(IWidget*)child atIndex:(NSNumber*)index;

/**
 * Set a widget property value.
 * @param key Widget's property name that should be set.
 * @param value Widget's proeprty value that should be set.
 * @return One of the following values:
 * - MAW_RES_OK if the property was set.
 * - MAW_RES_INVALID_PROPERTY_NAME if the property name was invalid.
 * - MAW_RES_INVALID_PROPERTY_VALUE if the property value was invalid.
 * - #MAW_RES_ERROR otherwise.
 */
- (int)setPropertyWithKey:(NSString*)key toValue:(NSString*)value;

/**
 * Recalculate its and children size.
 * If needed and possible the parent will be resized too.
 */
- (void)layout;

- (void)superLayoutSubviews;


@end
