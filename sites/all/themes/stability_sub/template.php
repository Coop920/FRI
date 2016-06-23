<?php 

function stability_sub_form_uc_cart_checkout_alter(&$form, &$form_state, $form_id) {
  dpm($form);
}

/**
 * Implementation of hook_preprocess_page().
 */
function stability_sub_process_page(&$variables) {
  global $user;
  $variables['login_account_links'] = '';
  if (theme_get_setting('login_account_links') || module_exists('uc_cart')) {
    $output = '';
    if(theme_get_setting('login_account_links')) {
      $output .= '<span class="login">
        <i class="fa fa-lock"></i> ' . l(($user->uid ? t('My Account') : t('Login')), 'user') . '
      </span>';
      $output .= $user->uid ? '<span class="logout"><i class="fa fa-sign-out"></i> ' . l(t('Logout'), 'user/logout') . '</span>' : '';
      $output .= !$user->uid ? '<span class="register"><i class="fa fa-pencil-square-o"></i>' . t('Not a Member?'). ' ' . l(t('Register'), 'user/register') . '</span>' : '';
    }
    if(module_exists('uc_cart')) {
      $output .= '<a href="/pay-invoice" style="margin-right: 10px;">Pay Invoice</a>';  
      $output .= '<span class="cart">
        <i class="fa fa-shopping-cart"></i> ' . l(t('Shopping Cart'), 'cart') . '
      </span>';      
    }
    $variables['login_account_links'] = '
      <div class="header-top-right">
        ' . $output . '
      </div>';
  }

  $header_top_menu_tree = module_exists('i18n_menu') ? i18n_menu_translated_tree('menu-header-top-menu') : menu_tree('menu-header-top-menu');
  $variables['header_top_menu_tree'] = drupal_render($header_top_menu_tree);
  // Process Slideshow Sub Header
  if(theme_get_setting('sub_header') == 5 || (arg(2) == 'sub-header'  && arg(3) == '5')) {
    drupal_add_js(drupal_get_path('theme', 'stability') . '/vendor/jquery.glide.min.js');
  }
  if(theme_get_setting('retina')) {
    drupal_add_js(drupal_get_path('theme', 'stability') . '/vendor/jquery.retina.js');
  }
  drupal_add_js(array('stability' => array('flickr_id' => theme_get_setting('flickr_id'), 'logo_sticky' => theme_get_setting('logo_sticky'))), 'setting');
}