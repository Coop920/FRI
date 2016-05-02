<?php

/**
 * @file
 * Default Rules configurations.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function uc_fee_default_rules_configuration() {
  $configs = array();

  $fees = uc_fee_get_fees();
  foreach ($fees as $fee) {
    // Setup a default configuration for customer checkout notifications.
    $rule = rules_reaction_rule();
    $rule->label = $fee->name;
    $rule->active = TRUE;
    $rule->event('calculate_fees')
      ->action('uc_fee_action_apply_fee_'. $fee->fid, array(
        'order:select' => 'order',
        'fee' => $fee->fid,
      ));
  
    $configs['uc_fee_'. $fee->fid] = $rule;
  }

  return $configs;
}
