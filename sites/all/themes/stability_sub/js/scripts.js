(function($){

	Drupal.behaviors.miscActions = {
	  attach: function(context, settings) {

		$(document).ready(function(){
			$( "div.category-description h2:contains('Changing Your Bed Within Your Package')" ).after( "<p>Tip: Products in this section only apply if you're renting a package.</p>" );

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

	
  // Event rental calculator.
	if ($('.webform-calendar').length) {
		var startDate      = new Date();
		var endDate        = new Date();
		var deliveryNeeded = true;
		var numChairs      = 0;
		var numTables      = 0;
		var deliveryMin    = 80;
		var tableRates     = {
			'daily': 4,
			'weekend': 4,
			'weekly': 7.50,
			'monthly': 10,
			'delivery': 4
		};  
		var chairRates     = {
			'daily': 0.40,
			'weekend': 0.60,
			'weekly': 0.80,
			'monthly': 1.60,
			'delivery': 0.80
		};

		// Hide old select date field elements.
		//$('.webform-datepicker > div:not(.textfield-calendar)').hide();

		// Ensure we work with simple dates, can cause issues otherwise.
		startDate.setHours(0,0,0,0);
		endDate.setHours(0,0,0,0);

		// Disable weekends.
		//$(".webform-calendar").datepicker({ beforeShowDay: $.datepicker.noWeekends });

		$('#edit-submitted-number-of-folding-tables').change(function () { 
			numTables = this.value;
			updateEventRentalEstimate();
		});
		$('#edit-submitted-number-of-folding-chairs').change(function () { 
			numChairs = this.value;
			updateEventRentalEstimate();
		});
		$('#edit-submitted-i-am-going-to-pickup-and-return-the-furniture-1').change(function () { 
			deliveryNeeded = !this.checked;
			updateEventRentalEstimate();
		});
		$('#edit-submitted-event-start-month').change(function () { 
			startDate.setMonth(this.value - 1);
			updateEventRentalEstimate();
		});
		$('#edit-submitted-event-start-day').change(function () { 
			startDate.setDate(this.value);
			console.log(this.value);
			updateEventRentalEstimate();
		});
		$('#edit-submitted-event-start-year').change(function () { 
			startDate.setFullYear(this.value);
			updateEventRentalEstimate();
		});
		$('#edit-submitted-event-end-month').change(function () { 
			endDate.setMonth(this.value - 1);
			updateEventRentalEstimate();
		});
		$('#edit-submitted-event-end-day').change(function () { 
			endDate.setDate(this.value);
			updateEventRentalEstimate();
		});
		$('#edit-submitted-event-end-year').change(function () { 
			endDate.setFullYear(this.value);
			updateEventRentalEstimate();
		});
	}
	
	function updateEventRentalEstimate() {
		var estimate = 0;
		var delivery = 0;
		
		// Calucate the number of days requested.
		var oneDay = 24 * 60 * 60 * 1000; 
    var days   = Math.round(Math.abs((startDate.getTime() - endDate.getTime()) / oneDay));
		
		// Determine rental rate to use and length.
		var rate    = 'daily';
		var divisor = 1;
		if (days > 29) {
			rate    = 'monthly';
			divisor = 31;
		} else if (days > 6) {
			rate    = 'weekly';
			divisor = 7;
		} else if (days === 3 && startDate.getDay() === 5 && endDate.getDay() === 1) {
			rate    = 'weekend';
			divisor = 3;
		}
		var ratePeriod = Math.ceil(days / divisor);
		
		// Determine delivery cost.
		if (deliveryNeeded) {
			delivery = (numTables * tableRates.delivery) + (numChairs * chairRates.delivery);
			delivery = delivery > 80 ? delivery : 80;
		}
		
	
		estimate = ((numTables * tableRates[rate]) * ratePeriod) + ((numChairs * chairRates[rate]) * ratePeriod);
		$('#event-rental-estimate').html(estimate);
		$('#event-rental-delivery').html(delivery);
		$('#event-rental-total').html(estimate + delivery);
	}
	
	// Maked node content tables table responsive.
	$('.node table').addClass('table').wrap('<div class="table-responsive"></div>');

	// Appending iframe to checkout screen
	$('#authorization-form').html('<iframe frameborder="0" height="800px" scrolling="no" src="https://na2.docusign.net/Member/PowerFormSigning.aspx?PowerFormId=ccf6c8ef-dd02-4479-b3b2-5b89e9e1074f" width="100%"></iframe>');
	
})(jQuery);