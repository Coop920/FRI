<?php

/**
 * AJAX callback to return a Tableau report link.
 */
function common_get_report_link_tableau_ajax( $workbook, $view, $username, $tabs ) {
  // Init
  $out = FALSE;
  
  // Get the tableau ticket
  $ticket = common_return_tableau_report_ticket( $username );
  
  // Use the ticket to formulate the URL
  if( $ticket ) :
    $out = common_return_tableau_report_link( $ticket, $workbook, $view, $tabs );
  endif;
  
  // Output and close up
  print $out;
  exit(0);
}


/**
 * Helper function to get the Tableau username.
 */
function common_return_tableau_username( $account, $node ) {

  // Initialize the Tableau username
  $username = FALSE;
  $default_username = 'd2d-portal-user';
  
  // Validate that we have filter terms for the user
  if( 
    !isset($GLOBALS['nodes']['user_customer_term']) 
    || !is_array($GLOBALS['nodes']['user_customer_term'])
    || count($GLOBALS['nodes']['user_customer_term']) < 1
  ) :
    return $default_username;
  else :
    $user_filter_terms = $GLOBALS['nodes']['user_customer_term'];
  endif;
  
  // Get the filters field on the node
  $node_filter_tids = array();
  switch( $node->type ) :
    case 'report_link':
      if( isset($node->field_customer[LANGUAGE_NONE]) && is_array($node->field_customer[LANGUAGE_NONE]) ) :
        foreach( $node->field_customer[LANGUAGE_NONE] as $one_customer ) :
          $node_filter_tids[ $one_customer['tid'] ] = $one_customer['tid'];
        endforeach;
      endif;
    break;
    
    default:
      // do nothing
    break;
  endswitch;
  
  // Get the terms
  $node_filter_terms = taxonomy_term_load_multiple( $node_filter_tids );
  
  // Look for a match between node and user terms
  foreach( $node_filter_terms as $one_node_filter_tid => $one_node_filter_term ) :
    if( isset( $user_filter_terms[ $one_node_filter_tid ] ) ) :
      $matching_filter_term = $user_filter_terms[ $one_node_filter_tid ];
      if( isset($matching_filter_term->field_tableau_user[LANGUAGE_NONE][0]['value']) ) :
        // Set value for output
        $username = $matching_filter_term->field_tableau_user[LANGUAGE_NONE][0]['value'];
        
        // We can stop looking for matches
        break;
      endif;
    endif;
  endforeach;
  
   
  // Nothing? Use a default
  if( !$username ) :
    $username = $default_username;
  endif;

  return $username;
}

/**
 * Helper function to get a Tableau report ticket.
 *
 * Return a Tableau ticket. A ticket grants access one time to a particular workbook & view from a particular server.
 */
function common_return_tableau_report_ticket( $username ) {
  // Init output
  $out = FALSE;

  //-----[ BEGIN Get Tableau Ticket ]-----  
  // Init CURL connection
  $ch = curl_init();
 
  // Init params for post
  $post_params = array(
    'username' => $username,
  );
  
  // Set CURL options
  curl_setopt_array( $ch, array(
    CURLOPT_URL => ENV_TABLEAU_TICKET_HOST,
    CURLOPT_RETURNTRANSFER => TRUE,
    CURLOPT_POST           => true,
    CURLOPT_POSTFIELDS     => $post_params,
  ) );

  // Execute CURL
  $ticket = curl_exec($ch);

  // Output errors
  // print '<hr>Error number:<br>';
  // var_dump( curl_errno($ch) );
  // print '<hr>Error message:<br>';
  // var_dump( curl_error($ch) );
  // print '<hr>';

  // Clean up
  curl_close($ch);
  //-----[ END Get Tableau Ticket ]-----

  // Assemble URL w ticket
  $out = $ticket;
  
  // Good job. Let's go home
  return $out;

}

/**
 * Helper function to assemble a Tableau report URL out of requisite pieces
 */
function common_return_tableau_report_link( $ticket, $workbook, $view, $tabs ) {
  $out = ENV_TABLEAU_CONTENT_HOST.$ticket.'/views/'.$workbook.'/'.$view;
  
  switch( $tabs ) :
    case 'yes':
    case 'no':
      $out.= '?:tabs='.$tabs;
    break;
  endswitch;
  
  return $out;
}

/**
 * Helper function to assemble the Drupal path for a Tableau report out of the requisite pieces
 */
function common_return_tableau_report_drupal_path( $ticket, $workbook, $view ) {
  $out = 'get-report/tableau/'.$ticket.'/'.$workbook.'/'.$view;

  return $out;
}
