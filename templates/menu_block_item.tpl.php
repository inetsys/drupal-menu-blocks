<?php print l($item['label'], $item['link'], $item['options']); ?>
<?php if(isset($item['children']) && !empty($item['children'])) : ?>
	<ul>
		<?php foreach($item['children'] as $child) : ?>
			<li<?php if($child['active_trail']): ?> class="active-trail"<?php endif; ?>><?php print theme('menu_block_item', array('item' => $child)); ?></li>
		<?php endforeach; ?>
	</ul>
<?php endif; ?>