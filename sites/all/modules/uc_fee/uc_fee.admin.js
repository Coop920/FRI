(function($) {

Drupal.behaviors.ucFeeAdmin = {
  attach: function (context) {
    for (var j in Drupal.settings.ucUsedFees) {
      var current  = Drupal.settings.ucUsedFees[j];
      
      // override checkbox
      var temp = $('#edit-uc-fees-enable-fee-override-'+current);

      if (temp.is(':checked')) {
        $('#edit-uc-fees-'+current).show(0);
      }
      else {
        $('#edit-uc-fees-'+current).hide(0);
      }
      
      $('#edit-uc-fees-enable-fee-override-'+current).click(function(){
        var id = this.id.substring(33);
        if (this.checked) {
          $('#edit-uc-fees-'+id).show(0);
        }
        else {
          $('#edit-uc-fees-'+id).hide(0);
        }
      });
     
      // exclude checkbox
      var temp2 = $('#edit-uc-fees-'+current+'-exclude');
      if (temp2.is(':checked')) {
        $('#edit-uc-fees-'+current+'-price').attr('disabled', 'disabled');
      }
      else {
        $('#edit-uc-fees-'+current+'-price').attr('disabled', '');
      }
      
      $('#edit-uc-fees-'+current+'-exclude').click(function(){
        var id = this.id.substr(13,1);
        if (this.checked) {
          $('#edit-uc-fees-'+id+'-price').attr('disabled', 'disabled');
        }
        else {
          $('#edit-uc-fees-'+id+'-price').attr('disabled', '');
        }
      });
      
    };
	}
};

})(jQuery);