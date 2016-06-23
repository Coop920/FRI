<?php

/**
 * Helper function to get the children of a customer
 */
function common_get_customer_children( $customer_id ) {
  $out = FALSE;
  
  if( empty($customer_id) ) :
    return $out;
  endif;
  
  $children = taxonomy_get_tree( VID_CUSTOMERS, $customer_id, 1 );
  
  if( is_array($children) && count($children) ) :
    $out = array();
    foreach( $children as $one_child ) :
      // Rekey by weight so we can sort
      $out[ $one_child->weight ] = $one_child;
    endforeach;
    ksort($out);
  endif;

  return $out;
}

/**
 * Helper function to return HTML for a customer's children
 */
function common_build_html_customer_children( $customer, $children, $header, $limit=FALSE, $more_link=FALSE ) {
  $out = '';
  
  if( !$header ) :
    return $out;
  elseif( !is_array($children) || count($children)<1 ) :
    return $out;
  endif;
  
  $child_counter = 0;
  foreach( $children as $one_child ) :
    $one_child_term = taxonomy_term_load( $one_child->tid );

    if( !$one_child_term || !isset($one_child_term->field_customer_type[LANGUAGE_NONE][0]['value']) ) :
      continue;
    elseif( $one_child_term->field_customer_type[LANGUAGE_NONE][0]['value'] == 'coi' ) :
      continue;
    endif;
      
    
    if( $limit && $child_counter>=$limit ) :
      break;
    else :
      ++$child_counter; 
    endif;
    
    $out.= '
  <div class="one-customer-child">'.l($one_child->name, '#').'</div>';
  endforeach; 
  
  // If we have any output, wrap it up
  if( strlen($out)>0 ) :
  
    // Add a more link if necessary
    if( $more_link ) :
      $out.= '
  <div class="more-link">'.l('See all', '#').'</div>';
    endif;
    
    // Add a header and wrappers
    $out = '
<header>'.$header.': </header>
<section>'.$out.'</section>';

  endif;
  
  // Good job. Let's go home
  return $out;
}

/*
 * Helper function to build HTML for the customer quicklinks
 */
function common_build_html_customer_quicklinks( $customer ) {
  $content_types = array(
    'data_theme' => 'Data Themes',
    'dataset' => 'Data Sets',
    'project' => 'Projects',
    'reports' => 'Reports',
  );
  
  $out = '<header>'.$customer->title.' Quicklinks</header><section>';

  foreach( $content_types as $one_id => $one_label ) :
    $out.= '
<div class="'.$one_id.'">
  <a href="search-d2d?customer='.$customer->nid.'">
    <div class="one-icon one-icon-'.$one_id.'"></div>
    <p>'.$one_label.'</p>
  </a>
</div>';
  endforeach;
  
  $out.= '</section>';

  return $out;
}


/**
 * Helper function to return the HTML for a views-exposed-filter widget
 */
function common_build_html_views_exposed_filter( $id, $widget ) {
  $out = '<!-- BEGIN widget '.$id.' -->';
  
  $out.= '<div id="'.$widget->id.'-wrapper" class="views-exposed-widget views-widget-'.$id.'">'."\n";

  if( !empty($widget->label) ) :
    $out.= '  <label for='.$widget->id.'">'.$widget->label.'</label>'."\n";
  endif;
  
  if( !empty($widget->operator) ) :
    $out.= '  <div class="views-operator">'.$widget->operator.'</div>'."\n";
  endif;

  $out.= '  <div class="views-widget">'.$widget->widget.'</div>'."\n";

  if( !empty($widget->description) ):
    $out.= '  <div class="description">'.$widget->description.'</div>'."\n";
  endif;
  
  $out.= '</div>';
  
  $out.= '<!-- END widget '.$id.' -->';
  
  return $out;
}
