<?php if($menu) : ?>
	<nav<?php if($html_id) : ?> id="<?php print $html_id; ?>"<?php endif; ?><?php if($html_classes): ?> class="<?php print implode(' ', $html_classes); ?>"<?php endif; ?>>
		<?php if($title) : ?>
			<header><h2><?php print $title; ?></h2></header>
		<?php endif; ?>
		<ul>
			<?php foreach($menu as $item): ?>
				<li<?php if($item['active_trail']): ?> class="active-trail"<?php endif; ?>><?php print theme('menu_block_item', array('item' => $item)); ?></li>
			<?php endforeach; ?>
		</ul>
	</nav>
<?php endif; ?>
