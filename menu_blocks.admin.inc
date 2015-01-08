<?php

function menu_blocks_settings_page($form, $form_state){
	$form = array();

	$options = array();
	for($i=1; $i<=10; $i++){
		$options[$i] = $i;
	}

	$form['menu_blocks_count'] = array(
		'#type' => 'select',
		'#title' => t('Number of blocks created by this module'),
		'#default_value' => variable_get('menu_blocks_count', 5),
		'#required' => TRUE,
		'#options' => $options
	);

	return system_settings_form($form);
}