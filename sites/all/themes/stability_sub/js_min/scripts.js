!function(i){Drupal.behaviors.mobileMenu={attach:function(e,n){i("#mobile-trigger").click(function(e){i("#mobile-trigger").toggleClass("active"),e.stopPropagation(),i("#block-awi-main-menu").slideToggle(300,"swing",function(){}),i("#block-awi-main-menu .menu-block-1 li.expanded").removeClass("active"),i("#block-awi-main-menu .menu-block-1 li.expanded .menu").css("display","none")}),i("#block-awi-main-menu .menu-block-1 li.expanded").click(function(){i(this).toggleClass("active"),i(this).children(".menu").slideToggle(300,"swing")})}},Drupal.behaviors.homepageSlider={attach:function(e,n){i(window).load(function(){i("#block-views-block-slideshow-block-1 .view-slideshow").flexslider({animation:"slide",selector:".view-content > .views-row",directionNav:!1,start:function(e){i("body").removeClass("loading")}})})}},Drupal.behaviors.equalHeights={attach:function(e,n){equalheight=function(e){var n,o=0,t=0,l=new Array;i(e).each(function(){if(n=i(this),i(n).height("auto"),topPostion=n.position().top,t!=topPostion){for(currentDiv=0;currentDiv<l.length;currentDiv++)l[currentDiv].height(o);l.length=0,t=topPostion,o=n.height(),l.push(n)}else l.push(n),o=o<n.height()?n.height():o;for(currentDiv=0;currentDiv<l.length;currentDiv++)l[currentDiv].height(o)})},i(window).load(function(){i("body").innerWidth()}),i(window).resize(function(){i("body").innerWidth()})}}}(jQuery);