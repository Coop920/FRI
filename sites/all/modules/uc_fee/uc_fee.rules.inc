<?php

/**
 * @file
 * Rules hooks for uc_fee.module.
 */

/**
 * Implements hook_rules_data_info().
 */
function uc_fee_rules_data_info() {

  $entities['uc_fee'] = array(
    'label' => t('Ubercart fee object'),
    'group' => t('Ubercart'),
    'property info' => array(
      'fid' => array(
        'type' => 'integer',
        'label' => t('Fee ID'),
      ),
    ),
  );

  return $entities;
}

/**
 * Implements hook_rules_event_info().
 */
function uc_fee_rules_event_info() {
  $events['calculate_fees'] = array(
    'label' => t('Calculate fees'),
    'group' => t('Fees'),
    'variables' => array(
      'order' => array(
        'type' => 'uc_order',
        'label' => t('Order'),
      ),
      'user' => array(
        'type' => 'user',
        'label' => t('User account'),
      ),
    ),
  );

  return $events;
}


/**
 * Implementation of hook_rules_action_info().
 */
function uc_fee_rules_action_info() {
  $actions = array();

  $fees = uc_fee_get_fees();
  foreach ($fees as $fee) {
    $actions['uc_fee_action_apply_fee_'. $fee->fid] = array(
      'label' => t('Charge a fee: '. $fee->name),
      'group' => t('Fees'),
      'base' => 'uc_fee_action_apply_fee',
      'parameter' => array(
        'order' => array(
          'type' => 'uc_order',
          'label' => t('Order'),
        ),
        'fee' => array(
          'type' => 'integer',
          'label' => t('Fee'),
          'default value' => $fee->fid,
        ),
      ),
    );
  }

  return $actions;
}


/**
 * Rules callback to add a fee.
 *
 * @param $order
 *   The order object being considered.
 * @param $fee
 *   The fee.
 * @return
 *   The line item array representing the fee.
 */
function uc_fee_action_apply_fee($order, $fid) {
  $amount = 0;
  $applications = 0;
  $fid = $fid['value'];
  $fee = uc_fee_load($fid);
  $update = FALSE;
  foreach($order->line_items as $li) {
    if ($li['type'] == 'fee' && $li['title'] == $fee->name) {
      $update = TRUE;
      $id = $li['line_item_id'];
    }
  }
  if (is_array($order->products)) {
    foreach ($order->products as $product) {
      // do not apply the fee more than the amount of times specified in max_applications
      if ($fee->max_applications && $applications >= $fee->max_applications) {
        break;
      }
      $product_fee = uc_fee_load($fee->fid, $product->nid, 'product');
      if (!$product_fee->is_active) {
        continue;
      }
      //TODO: should ask the user if they want to use qty or not
      $remaining_applications =  $fee->max_applications - $applications;
      $this_applications = $fee->max_applications ? min($product->qty, $remaining_applications) : $product->qty;
      
      switch ($product_fee->type) {
        case UC_FEE_TYPE_ABSOLUTE:
          $price = $product_fee->price;
          break;
          
        case UC_FEE_TYPE_PERCENTAGE:
          $price = $product->price * ($product_fee->price / 100);
          break;
      }
      $amount += $price * $this_applications;
      $applications += $this_applications;
    }
  }
  if ($amount) {
    if ($update == TRUE) {
      uc_order_update_line_item($id, $fee->name, $amount);
    } else {
      uc_order_line_item_add($order->order_id, 'fee', $fee->name, $amount);
    }
  }
}
