/**
 * @file
 * Handle asynchronous requests to calculate fees.
 */
 
(function($) {

var pane = '';
if ($("input[name*=delivery_]").length) {
  pane = 'delivery'
}
else if ($("input[name*=billing_]").length) {
  pane = 'billing'
}

Drupal.behaviors.ucChangeFee = {
  attach: function (context) {
    $("select[name*=delivery_country], "
      + "select[name*=delivery_zone], "
      + "input[name*=delivery_city], "
      + "input[name*=delivery_postal_code], "
      + "select[name*=billing_country], "
      + "select[name*=billing_zone], "
      + "input[name*=billing_city], "
      + "input[name*=billing_postal_code]").change(getFee);
    $("input[name*=copy_address]").click(getFee);
    $('#edit-panes-payment-current-total').click(getFee);
	}
};


/**
 * Get fee calculations for the current cart and line items.
 */
var getFee = function() {
  var order = Drupal.settings.ucURL.ucOrder;

  if (!!order) {
    $.ajax({
      type: "POST",
      url: Drupal.settings.ucURL.calculateFee,
      data: 'order=' + order,
      dataType: "json"
    });
  }
}

})(jQuery);
