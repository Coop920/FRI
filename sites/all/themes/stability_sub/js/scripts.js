(function($){

	Drupal.behaviors.miscActions = {
	  attach: function(context, settings) {

		$(document).ready(function(){


		});

	  }
	};


	Drupal.behaviors.equalHeights = {
	  attach: function(context, settings) {

		equalheight = function(container){

			var currentTallest = 0,
					 currentRowStart = 0,
					 rowDivs = new Array(),
					 $el,
					 topPosition = 0;
			 $(container).each(function() {

				 $el = $(this);
				 $($el).height('auto');
				 topPostion = $el.position().top;

				 if (currentRowStart != topPostion) {
					 for (currentDiv = 0 ; currentDiv < rowDivs.length ; currentDiv++) {
						 rowDivs[currentDiv].height(currentTallest);
					 }
					 rowDivs.length = 0; // empty the array
					 currentRowStart = topPostion;
					 currentTallest = $el.height();
					 rowDivs.push($el);
				 } else {
					 rowDivs.push($el);
					 currentTallest = (currentTallest < $el.height()) ? ($el.height()) : (currentTallest);
				}
				 for (currentDiv = 0 ; currentDiv < rowDivs.length ; currentDiv++) {
					 rowDivs[currentDiv].height(currentTallest);
				 }
			 });
			}

			$(window).load(function() {
				//equalheight('header > .region');

	      		var currWindowWidth = $('body').innerWidth();
				if (currWindowWidth <= 600) {

				}
			});


			$(window).resize(function(){
				//equalheight('header > .region');

	      		var currWindowWidth = $('body').innerWidth();
				if (currWindowWidth <= 600) {
				}
				if (currWindowWidth >= 600) {
				}
			});

	  }
	};


})(jQuery);