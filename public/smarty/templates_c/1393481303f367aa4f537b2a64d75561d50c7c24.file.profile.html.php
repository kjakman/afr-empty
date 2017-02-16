<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:06:13
         compiled from "/web/comps/php/apt-dev/smarty/templates/profile.html" */ ?>
<?php /*%%SmartyHeaderCode:66443038551a74e9ef2f85-11294210%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '1393481303f367aa4f537b2a64d75561d50c7c24' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/profile.html',
      1 => 1427900773,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '66443038551a74e9ef2f85-11294210',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551a74ea17ab29_62511232',
  'variables' => 
  array (
    'scope' => 0,
    'tag' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551a74ea17ab29_62511232')) {function content_551a74ea17ab29_62511232($_smarty_tpl) {?>
<?php if (($_smarty_tpl->tpl_vars['scope']->value['edit'])) {?>
<div class="container">
	<div class="row">
    <form class="form" action="#" method="post" id="profileForm" data-obj_type="user_profile">
     <?php echo $_smarty_tpl->getSubTemplate (((string)$_smarty_tpl->tpl_vars['template_dir']->value)."/include/profile_form.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

      <div class="form-group">
         <div class="col-xs-12">
          <br>
          <button class="btn btn-lg btn-success save-form" type="submit"><i class="fa fa-check"></i> <?php echo $_smarty_tpl->tpl_vars['scope']->value['dic']['save'];?>
</button>
          <button class="btn btn-lg btn-danger cancel-form"><i class="fa fa-close"></i> <?php echo $_smarty_tpl->tpl_vars['scope']->value['dic']['cancel'];?>
</button>
        </div>
      </div>

    </form>
  </div>
</div>
<?php } else { ?>

<div class="container margin-top">
	<div class="row">
		<div class="col-md-offset-2 col-md-8 col-lg-offset-3 col-lg-6">
    	<div class="well profile">
        <div class="col-sm-12">
          <div class="col-xs-12 col-sm-8">
            <h2><?php echo $_smarty_tpl->tpl_vars['scope']->value['display_name'];?>
</h2>
            <p><strong>Location: </strong><?php echo $_smarty_tpl->tpl_vars['scope']->value['city'];?>
</p>
            <?php if (($_smarty_tpl->tpl_vars['scope']->value['email_address'])) {?><p><strong>Email: </strong><?php echo $_smarty_tpl->tpl_vars['scope']->value['email_address'];?>
</p><?php }?>
            <?php if (($_smarty_tpl->tpl_vars['scope']->value['phone'])) {?><p><strong>Phone: </strong><?php echo $_smarty_tpl->tpl_vars['scope']->value['phone'];?>
</p><?php }?>
            <?php if (($_smarty_tpl->tpl_vars['scope']->value['mobile'])) {?><p><strong>Mobile: </strong><?php echo $_smarty_tpl->tpl_vars['scope']->value['mobile'];?>
</p><?php }?>
            <?php if (($_smarty_tpl->tpl_vars['scope']->value['interests'])) {?><p><strong>Interests: </strong><?php echo $_smarty_tpl->tpl_vars['scope']->value['interests'];?>
</p><?php }?>
            <?php if (($_smarty_tpl->tpl_vars['scope']->value['tags'])) {?>
            <p><strong>Tags: </strong>              
              <?php  $_smarty_tpl->tpl_vars['tag'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['tag']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['tags']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['tag']->key => $_smarty_tpl->tpl_vars['tag']->value) {
$_smarty_tpl->tpl_vars['tag']->_loop = true;
?>
                  <span class="tags"><?php echo $_smarty_tpl->tpl_vars['tag']->value;?>
</span>
              <?php } ?>               
            </p>
            <?php }?>
          </div>       
          <div class="col-xs-12 col-sm-4 text-center margin-top">
            <figure>
              <img src="<?php echo $_smarty_tpl->tpl_vars['scope']->value['photo'];?>
" alt="" class="img-circle img-responsive">
              <?php if (($_smarty_tpl->tpl_vars['scope']->value['rating'])) {?>
              <figcaption class="ratings">
                <p>Ratings
                <a href="#">
                  <span class="fa fa-star"></span>
                </a>
                <a href="#">
                  <span class="fa fa-star"></span>
                </a>
                <a href="#">
                  <span class="fa fa-star"></span>
                </a>
                <a href="#">
                  <span class="fa fa-star"></span>
                </a>
                <a href="#">
                   <span class="fa fa-star-o"></span>
                </a> 
                </p>
              </figcaption>
              <?php }?>
            </figure>
            <?php if (($_smarty_tpl->tpl_vars['scope']->value['auth_edit'])) {?>
            <p class='margin-top'><a class='social_button zocial green_back' href='?edit'><?php echo $_smarty_tpl->tpl_vars['scope']->value['dic']['edit'];?>
</a></p>
            <?php }?>
            </div>
        </div>  
        <?php if (($_smarty_tpl->tpl_vars['scope']->value['description'])) {?> 
        <div class="col-xs-12 margin-top">
          <p><strong>About Me: </strong></p><p><?php echo $_smarty_tpl->tpl_vars['scope']->value['description'];?>
</p>
        </div>
        <?php }?>
        
  <?php if (($_smarty_tpl->tpl_vars['scope']->value['followers'])) {?>        
        <div class="col-xs-12 divider text-center">
          <div class="col-xs-12 col-sm-4 emphasis">
            <h2><strong><?php echo $_smarty_tpl->tpl_vars['scope']->value['followers'];?>
</strong></h2>          
            <p><small>Followers</small></p>
            <button class="btn btn-success btn-block"><span class="fa fa-plus-circle"></span> Follow </button>
          </div>
          <div class="col-xs-12 col-sm-4 emphasis">
            <h2><strong><?php echo $_smarty_tpl->tpl_vars['scope']->value['followers'];?>
</strong></h2>          
            <p><small>Following</small></p>
            <?php if (($_smarty_tpl->tpl_vars['scope']->value['auth_edit'])) {?>
            <a href='?edit' class="btn btn-info btn-block"><span class="fa fa-user"></span> Edit Profile </a>
            <?php }?>
          </div>
          <div class="col-xs-12 col-sm-4 emphasis">
            <h2><strong>43</strong></h2>          
            <p><small>Snippets</small></p>
            <div class="btn-group dropup btn-block">
              <button type="button" class="btn btn-primary"><span class="fa fa-gear"></span> Options </button>
              <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown">
              <span class="caret"></span>
              <span class="sr-only">Toggle Dropdown</span>
              </button>
              <ul class="dropdown-menu text-left" role="menu">
              <li><a href="#"><span class="fa fa-envelope pull-right"></span> Send an email </a></li>
              <li><a href="#"><span class="fa fa-list pull-right"></span> Add or remove from a list  </a></li>
              <li class="divider"></li>
              <li><a href="#"><span class="fa fa-warning pull-right"></span>Report this user for spam</a></li>
              <li class="divider"></li>
              <li><a href="#" class="btn disabled" role="button"> Unfollow </a></li>
              </ul>
            </div>
          </div>   
        </div>    
  <?php }?>
      </div>                 
		</div>        
	</div>
</div>    
<?php }?>

<?php }} ?>
