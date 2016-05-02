(function($){

	Drupal.behaviors.mobileMenu = {
	  attach: function(context, settings) {

		// Mobile Menu
		$('#mobile-trigger').click(function(e) {
			$('#mobile-trigger').toggleClass('active');
			e.stopPropagation();
	    	$('#block-awi-main-menu').slideToggle(300, 'swing', function() {
	        //callback function after animation finished
			});

		    $('#block-awi-main-menu .menu-block-1 li.expanded').removeClass('active');
			$('#block-awi-main-menu .menu-block-1 li.expanded .menu').css('display', 'none');
		});
/*
		$('#block-awi-main-menu').bind('clickoutside', function (event) {
			$(this).slideUp(300, 'swing');
			$('#mobile-trigger').removeClass('active');
		});
*/
		// Sub Menu Items
		$('#block-awi-main-menu .menu-block-1 li.expanded').click(function () {
			$(this).toggleClass('active');
			$(this).children('.menu').slideToggle(300, 'swing');
		});

	  }
	};


	Drupal.behaviors.homepageSlider = {
	    attach: function(context, settings) {
		    $(window).load(function(){
		      	$('#block-views-block-slideshow-block-1 .view-slideshow').flexslider({
		        	animation: "slide",
		        	selector: ".view-content > .views-row",
		        	directionNav: false,
		        	start: function(slider){
		          	$('body').removeClass('loading');
		        	}
		      	});
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