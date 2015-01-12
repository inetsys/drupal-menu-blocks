<?php

function _menu_blocks_in_active_trail($path){
	$active_paths = &drupal_static(__FUNCTION__);
	// Gather active paths.
	if (!isset($active_paths)) {
		$active_paths = array();
		$trail = menu_get_active_trail();
		foreach($trail as $item){
			if(!empty($item['href'])){
				$active_paths[] = $item['href'];
			}
		}
	}

	return !empty($path) && $path != '<front>' && in_array($path, $active_paths);
}


function _menu_blocks_search_active_element($tree, $level, $current_level=1){
	$active_element = false;
	foreach($tree as $item){
		$item['link']['in_active_trail'] = _menu_blocks_in_active_trail($item['link']['link_path']);

		if(!$item['link']['in_active_trail']){
			continue;
		}
		if($current_level == $level){
			$active_element = $item;
			break;
		}
		if(isset($item['below']) && !empty($item['below'])){
			$active_element = _menu_blocks_search_active_element($item['below'], $level, $current_level+1);
		}
	}

	return $active_element;
}

function _menu_blocks_get_link_below($item, $current_level, $max_levels = 0){
	$list = array();

	if(isset($item['below']) && !empty($item['below'])){
		foreach($item['below'] as $level){
			$item = array(
				'link' => $level['link']['link_path'],
				'label' => $level['link']['link_title'],
				'options' => $level['link']['options'],
				'level' => $current_level,
				'active_trail' => _menu_blocks_in_active_trail($level['link']['link_path']),
			);
			if(!$max_levels || $max_levels > $current_level){
				$item['children'] = _menu_blocks_get_link_below($level, $current_level+1, $max_levels);
			}
			$list[] = $item;
		}
	}

	return $list;
}

function _menu_blocks_get_menu_tree($menu_name, $first_level = 1, $max_levels = 0){
	$tree = menu_tree_all_data($menu_name);
	$menu = array();

	if($first_level == 1){
		foreach($tree as $level){
			$item = array(
				'link' => $level['link']['link_path'],
				'options' => $level['link']['options'],
				'label' => $level['link']['link_title'],
				'level' => 1,
				'active_trail' => _menu_blocks_in_active_trail($level['link']['link_path']),
			);
			if(!$max_levels || $max_levels > 1){
				$item['children'] = _menu_blocks_get_link_below($level, 2, $max_levels);
			}
			$menu[] = $item;
		}
	}else{
		$active_element = _menu_blocks_search_active_element($tree, $first_level - 1);
		if(isset($active_element['below']) && !empty($active_element['below'])){
			$level = 1;
			foreach($active_element['below'] as $child){
				$item = array(
					'link' => $child['link']['link_path'],
					'options' => $child['link']['options'],
					'label' => $child['link']['link_title'],
					'level' => $level,
					'active_trail' => _menu_blocks_in_active_trail($child['link']['link_path']),
				);
				if(!$max_levels || $max_levels > 1){
					$item['children'] = _menu_blocks_get_link_below($child, 2, $max_levels);
				}
				$menu[] = $item;
			}
		}
	}

	return $menu;
}