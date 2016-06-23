<?php

// Define constants for block machine names
define( 'BLOCK_REPORT_LINKS', 'common_report_links' );
define( 'BLOCK_CUSTOMER_ABOUT', 'common_customer_about' );
define( 'BLOCK_CUSTOMER_CONTACT', 'common_customer_contact' );
define( 'BLOCK_CUSTOMER_MENU', 'common_customer_menu' );
define( 'BLOCK_NODE_AUTHOR_SIDEBAR', 'common_node_author_sidebar' );
define( 'BLOCK_LOGIN_BUTTON', 'common_login_button' );


/**
 * Implements hook_block_info().
 */
function common_block_info() {
  $blocks = array();

  $blocks[BLOCK_REPORT_LINKS] = array(
    'info' => t('Report Links'),
    'cache' => DRUPAL_NO_CACHE,
  );
  
  $blocks[BLOCK_CUSTOMER_ABOUT] = array(
    'info' => t('Customer: About Us'),
    'cache' => DRUPAL_NO_CACHE,
  );
  
  $blocks[BLOCK_CUSTOMER_CONTACT] = array(
    'info' => t('Customer: Contact People'),
    'cache' => DRUPAL_NO_CACHE,
  );
  
  $blocks[BLOCK_CUSTOMER_MENU] = array(
    'info' => t('Customer: Menu'),
    'cache' => DRUPAL_NO_CACHE,
  );

  $blocks[BLOCK_NODE_AUTHOR_SIDEBAR] = array(
    'info' => t('Content Author Sidebar'),
    'cache' => DRUPAL_NO_CACHE,
  );
  
  $blocks[BLOCK_LOGIN_BUTTON] = array(
    'info' => t('Login Button'),
    'cache' => DRUPAL_NO_CACHE,
  );
  
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function common_block_view($delta='') {
  $block = array();

  switch($delta) :

    case BLOCK_REPORT_LINKS :
      if( isset($GLOBALS['nodes']['page_node']->type) && $GLOBALS['nodes']['page_node']->type == 'report' ) :
        $block['subject'] = '';
        $block['content'] = _common_block_report_links( $GLOBALS['nodes']['page_node'] );
      else :
        // Don't show
        $block['subject'] = '';
        $block['content'] = '';
      endif;
    break;
    
    case BLOCK_CUSTOMER_ABOUT :
      if( isset($GLOBALS['nodes']['page_node_customer']) && !empty($GLOBALS['nodes']['page_node_customer']) ) :
        $block['subject'] = 'About Us';
        $block['content'] = _common_block_customer_about( $GLOBALS['nodes']['page_node_customer'] );
      else :
        // Don't show
        $block['subject'] = '';
        $block['content'] = '';
      endif;
    break;
    
    case BLOCK_CUSTOMER_CONTACT :
      if( isset($GLOBALS['nodes']['page_node_customer']) && !empty($GLOBALS['nodes']['page_node_customer']) ) :
        $block['subject'] = '';
        $block['content'] = _common_block_customer_contact( $GLOBALS['nodes']['page_node_customer'] );
      else :
        // Don't show
        $block['subject'] = '';
        $block['content'] = '';
      endif;
    break;
    
    case BLOCK_CUSTOMER_MENU :
      if( isset($GLOBALS['nodes']['page_node_customer']) && !empty($GLOBALS['nodes']['page_node_customer']) ) :
        $block['subject'] = $GLOBALS['nodes']['page_node_customer_term']->name.' Menu';
        $block['content'] = _common_block_customer_menu( $GLOBALS['nodes']['page_node_customer'] );
      else :
        // Don't show
        $block['subject'] = '';
        $block['content'] = '';
      endif;
    break;
    
    case BLOCK_NODE_AUTHOR_SIDEBAR :
      if( 
        !common_is_report_new( $GLOBALS['nodes']['page_node'] )
        && isset($GLOBALS['users']['page_node_author']) 
        && !empty($GLOBALS['users']['page_node_author']) 
      ) :
        $block['subject'] = 'Contact';
        $block['content'] = _common_block_content_author_sidebar( $GLOBALS['users']['page_node_author'] );
      else :
        // Don't show
        $block['subject'] = '';
        $block['content'] = '';
      endif;
    break;
    
    case BLOCK_LOGIN_BUTTON :
      $block['subject'] = '';
      $block['content'] = _common_block_login_button();
    break;

  endswitch;

  return $block;
}

/*
 * Functions to generate HTML for blocks
 */
function _common_block_report_links( $report ) {
  // Init output
  $out = '';
    
  // Build link html
  $report_links_html = array();

  if( isset($report->field_report_links[LANGUAGE_NONE]) && is_array($report->field_report_links[LANGUAGE_NONE]) ) :
    foreach( $report->field_report_links[LANGUAGE_NONE] as $one_link ) :
      $report_links_html[] = drupal_render( node_view($one_link['entity'], 'report_link_w_image') );
    endforeach;
  endif;
  
  // if( count($report_links_html)> 0 ) :
    // $front_page_link = '
// <div id="node-0" class="node node-report-link contextual-links-region clearfix" typeof="sioc:Item foaf:Document">


  // <div class="content">
    // <a href="'.url('node/'.$report->nid).'">
      // <div>
        // <div class="field field-name-field-single-image field-type-image field-label-hidden">
          // <div class="field-items">
            // <div class="field-item even">
              // <img typeof="foaf:Image" src="/sites/all/themes/d2d/images/icons/home.png" width="102" height="102" alt="" />
            // </div>
          // </div>
        // </div>
      // </div>
      // <h3>Report Home Page</h3>
    // </a>
  // </div>
// </div>';
    // array_unshift( $report_links_html, $front_page_link );
  // endif;
  
  $out.= '<ul class="bxSlider"><li>'.implode( '</li><li>', $report_links_html ).'</li></ul>';

  return $out;
}

function _common_block_customer_about( $customer ) {
  // Init output
  $out = '';
  
  // Render the field
  $body_render_data = field_view_field('node', $customer, 'body');
  $out.= render( $body_render_data );

  return $out;
}

function _common_block_customer_contact( $customer ) {
  // Init output
  $out = '';
  
  // Render the contact people
  if( is_array($customer->field_contact_people[LANGUAGE_NONE]) ) :
    // Get all UIDs
    $uids = array();
    foreach( $customer->field_contact_people[LANGUAGE_NONE] as $one_person ) :
      $uids[ $one_person['target_id'] ] = $one_person['target_id'];
    endforeach;
    
    // Get all users
    $contact_people = user_load_multiple( $uids );
    
    // Render each one
    $contact_people_html = array();
    if( is_array($contact_people) && count($contact_people)>0 ) :
      foreach( $contact_people as $one_uid => $one_person ) :
        $one_person_render_data = user_view( $one_person, 'contact_person' );
        $contact_people_html[] = '<div class="one-contact-person one-contact-person-'.$one_uid.'">'.render($one_person_render_data).'</div>';
      endforeach;
    endif;
  endif;
  
  if( count($contact_people_html)>0 ) :
    $out.= '<div class="contact-person-container">'.implode( '', $contact_people_html ).'</div>';
  endif;

  return $out;
}

function _common_block_customer_menu( $customer ) {
  // Init output
  $out = '';
  
  //-----[ BEGIN setup for sub-units of this customer ]-----
  // Init
  $customer_term = $sub_unit_header = $sub_units = $sub_unit_html = FALSE;
  
  // Get the corresponding taxonomy term
  if( isset($customer->field_customer_term[LANGUAGE_NONE][0]['target_id']) ) :
    $customer_term = taxonomy_term_load( $customer->field_customer_term[LANGUAGE_NONE][0]['target_id'] );
  endif;

  // Set sub-unit title
  if( $customer_term && isset($customer_term->field_customer_type[LANGUAGE_NONE][0]['value']) ) :
    switch( $customer_term->field_customer_type[LANGUAGE_NONE][0]['value'] ) :
      case 'Agency':
        $sub_unit_header = 'Organizations';
      break;
      
      case 'Organization':
        $sub_unit_header = 'Communities of Interest';
      break;
    endswitch;
  endif;
  
  // Get sub-units
  if( $customer_term && $sub_unit_header ) :
    $sub_units = common_get_customer_children( $customer_term->tid );
  endif;
  
  // Get sub-unit HTML
  $sub_unit_html = common_build_html_customer_children( $customer_term, $sub_units, $sub_unit_header, 5, TRUE );
  //-----[ END setup for sub-units of this customer ]-----
  
  $out = $sub_unit_html;
  
  return $out;
}


function _common_block_content_author_sidebar( $author ) {
  $out = '';
  
  $out.= '<p>'.$author->field_first_name['und'][0]['value']. ' '.$author->field_last_name['und'][0]['value'].'</p>';
  $out.= '<p><a href="mailto:'.$author->mail.'">'.$author->mail.'</a></p>';
  
  if( $author->field_phone['und'][0]['value'] ) :
    $out.= '<p>'.$author->field_phone['und'][0]['value'].'</p>';
  endif;
  
  return $out;
}


function _common_block_login_button() {
  $out = '';

  if( !user_is_logged_in() ) :
    $login_link = l( 'Login', 'user', array( 
      'query' => array( 'destination' => $_GET['q'] )
      ) 
    );
    $out.= '<p>'.$login_link.'</p>';
  else :
    $cust = taxonomy_term_load( $GLOBALS['users']['full_user']->field_customer[LANGUAGE_NONE][0]['tid'] );
    $csfile = file_load( $cust->field_customer_image[LANGUAGE_NONE][0]['fid'] );
    
    // Output welcome text
    $out.= '<span>Welcome '.$GLOBALS['users']['full_user']->field_first_name[LANGUAGE_NONE][0]['value'].' '.$GLOBALS['users']['full_user']->field_last_name[LANGUAGE_NONE][0]['value'].' </span>';
    
    // Try to add the logo too
    if( $csfile ) :
      $imageurl = image_style_url('customer_square', $csfile->uri);
      $out.= '<img id="custlogo" src="'.$imageurl.'" /></a>';																		
    endif;
  endif;
  
  return $out;
}

