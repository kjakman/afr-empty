<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:05:20
         compiled from "/web/comps/php/apt-dev/smarty/templates/_rental-edit-description.html" */ ?>
<?php /*%%SmartyHeaderCode:1454307736551c09300b5b17-04671724%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '5cc732f95b688cdd4117c719ace88115a217dedb' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_rental-edit-description.html',
      1 => 1427900720,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1454307736551c09300b5b17-04671724',
  'function' => 
  array (
  ),
  'variables' => 
  array (
    'user' => 0,
    'site' => 0,
    'scope' => 0,
  ),
  'has_nocache_code' => false,
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c0930107bb1_47389024',
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c0930107bb1_47389024')) {function content_551c0930107bb1_47389024($_smarty_tpl) {?>
                    <h4>Description</h4>
                    <form id="desc-edit-form" class="ajax-submit" data-handler="save">
                      <input name="user_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['user']->value['id'];?>
" />
                      <input name="site_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['id'];?>
" />
                      <input name="property_id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
" />
                      <input name="property_type" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
" />
                      <input name="obj_type" type="hidden" value="property_description" />
                      <input name="id" type="hidden" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['description_id'];?>
" />
                  
                      <div class="form-group form-group-icon-left">
                          <label>Long Description</label>
                          <textarea name="description" class="summernote form-control" placeholder="Enter your description here..." ><?php echo $_smarty_tpl->tpl_vars['scope']->value['description'];?>
</textarea>
                      </div>
                      <hr>
                      <input type="submit" class="btn btn-primary" value="Save Changes">                      
                    </form>


<?php }} ?>
