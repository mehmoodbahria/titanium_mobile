define(["Ti/_/Layouts/Base", "Ti/_/declare", "Ti/UI"], function(Base, declare, UI) {

	return declare("Ti._.Layouts.Vertical", Base, {

		_doLayout: function(element, width, height, isWidthSize, isHeightSize) {
			var computedSize = this._computedSize = {width: 0, height: 0},
				currentTop = 0,
				children = element.children,
				availableHeight = height,
				childrenWithFillHeight = false;
				
			// Determine if any children have fill height
			for (var i = 0; i < children.length; i++) {
				children[i].height === UI.FILL && (childrenWithFillHeight = true);
			}
				
			// Measure the children
			if (childrenWithFillHeight) {
				for (var i = 0; i < children.length; i++) {
					var child = children[i];
					if (child.height !== UI.FILL) {
						if (child._markedForLayout) {
							child._doLayout({
								origin: {
							 		x: 0,
							 		y: 0
							 	},
							 	isParentSize: {
							 		width: isWidthSize,
							 		height: isHeightSize
							 	},
							 	boundingSize: {
							 		width: width,
							 		height: height
							 	},
							 	alignment: {
							 		horizontal: this._defaultHorizontalAlignment,
							 		vertical: this._defaultVerticalAlignment
							 	},
								positionElement: false,
						 		layoutChildren: true
							});
						}
						availableHeight -= child._measuredHeight;
					}
				}
			}
			
			// Layout the children
			for(var i = 0; i < children.length; i++) {
				
				// Layout the child
				var child = children[i],
					isHeightFill = child.height === UI.FILL;
				if (child._markedForLayout) {
					child._doLayout({
					 	origin: {
					 		x: 0,
					 		y: currentTop
					 	},
					 	isParentSize: {
					 		width: isWidthSize,
					 		height: isHeightSize
					 	},
					 	boundingSize: {
					 		width: width,
					 		height: isHeightFill ? availableHeight : height
					 	},
					 	alignment: {
					 		horizontal: this._defaultHorizontalAlignment,
					 		vertical: this._defaultVerticalAlignment
					 	},
					 	positionElement: true,
					 	layoutChildren: !childrenWithFillHeight || isHeightFill
				 	});
				 }
				
				// Update the size of the component
				var rightMostEdge = child._measuredWidth + child._measuredLeft + child._measuredBorderSize.left + child._measuredBorderSize.right + child._measuredRightPadding;
				currentTop = child._measuredHeight + child._measuredTop + child._measuredBorderSize.top + child._measuredBorderSize.bottom + child._measuredBottomPadding;
				rightMostEdge > computedSize.width && (computedSize.width = rightMostEdge);
				currentTop > computedSize.height && (computedSize.height = currentTop);
			}
			return computedSize;
		},
		
		_defaultHorizontalAlignment: "center",
		
		_defaultVerticalAlignment: "top"

	});

});
