<?php /* Smarty version Smarty-3.1.20, created on 2015-04-02 06:54:26
         compiled from "/web/comps/php/apt-dev/smarty/templates/_user-profile-overview.html" */ ?>
<?php /*%%SmartyHeaderCode:1333054518551c173cc8aee3-94823690%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'dd0560bc520cfd446341365469534d41360b494f' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/_user-profile-overview.html',
      1 => 1427957666,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1333054518551c173cc8aee3-94823690',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551c173ccaeed9_84497155',
  'variables' => 
  array (
    'scope' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551c173ccaeed9_84497155')) {function content_551c173ccaeed9_84497155($_smarty_tpl) {?>
                    <h4>Traveled Stats</h4>
                    <ul class="list list-inline user-profile-statictics mb30">
                        <li><i class="fa fa-dashboard user-profile-statictics-icon"></i>
                            <h5>420</h5>
                            <p>Miles</p>
                        </li>
                        <li><i class="fa fa-globe user-profile-statictics-icon"></i>
                            <h5>2%</h5>
                            <p>World</p>
                        </li>
                        <li><i class="fa fa-building-o user-profile-statictics-icon"></i>
                            <h5>15</h5>
                            <p>Cities</p>
                        </li>
                        <li><i class="fa fa-flag-o user-profile-statictics-icon"></i>
                            <h5>3</h5>
                            <p>Countries</p>
                        </li>
                        <li><i class="fa fa-plane user-profile-statictics-icon"></i>
                            <h5>20</h5>
                            <p>Trips</p>
                        </li>
                    </ul>
                    <?php if (($_smarty_tpl->tpl_vars['scope']->value['description'])) {?>
                    <h3>About</h3>
                    <?php echo $_smarty_tpl->tpl_vars['scope']->value['description'];?>

                    <?php }?>
                    <div id="map-canvas" style="width:100%; height:400px;"></div>


<?php }} ?>
