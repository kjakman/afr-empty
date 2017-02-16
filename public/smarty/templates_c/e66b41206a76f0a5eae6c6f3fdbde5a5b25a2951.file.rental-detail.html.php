<?php /* Smarty version Smarty-3.1.20, created on 2015-04-01 15:59:41
         compiled from "/web/comps/php/apt-dev/smarty/templates/rental-detail.html" */ ?>
<?php /*%%SmartyHeaderCode:1224482072551ba8d86c22d2-63045487%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    'e66b41206a76f0a5eae6c6f3fdbde5a5b25a2951' => 
    array (
      0 => '/web/comps/php/apt-dev/smarty/templates/rental-detail.html',
      1 => 1427903981,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1224482072551ba8d86c22d2-63045487',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.20',
  'unifunc' => 'content_551ba8d8c09d96_36447405',
  'variables' => 
  array (
    'scope' => 0,
    'image' => 0,
    'user' => 0,
    'site' => 0,
    'fac' => 0,
    'golf' => 0,
    'query_string' => 0,
    'apt' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_551ba8d8c09d96_36447405')) {function content_551ba8d8c09d96_36447405($_smarty_tpl) {?>
        <div class="container">
            <ul class="breadcrumb">
                <li><a href="/">Home</a>
                </li>
                <li><a href="#">Serviced Apartments</a>
                </li>
                <li class="active"><?php echo $_smarty_tpl->tpl_vars['scope']->value['name'];?>
</li>
            </ul>
            <?php echo $_smarty_tpl->tpl_vars['scope']->value['pager'];?>

            <div class="booking-item-details">
                <header class="booking-item-header">
                    <div class="row">
                        <div class="col-md-9">
                            <h2 class="lh1em"><?php echo $_smarty_tpl->tpl_vars['scope']->value['name'];?>
</h2>
                            <p class="lh1em text-small"><i class="fa fa-map-marker"></i> <?php echo $_smarty_tpl->tpl_vars['scope']->value['address'];?>
</p>
                            <ul class="list list-inline text-small">
                                <li><a href="/profile/<?php echo $_smarty_tpl->tpl_vars['scope']->value['host_id'];?>
?view=_user-profile-message.html&amp;parent_type=<?php echo $_smarty_tpl->tpl_vars['scope']->value['type'];?>
&amp;parent_id=<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
"><i class="fa fa-envelope"></i> Contact host</a>
                                </li>
                                <!--li><a href="#"><i class="fa fa-home"></i> Agent Website</a>
                                </li>
                                <li><i class="fa fa-phone"></i> +1 (520) 466-9587</li-->
                            </ul>
                        </div>
                        <div class="col-md-3">
                            <p class="booking-item-header-price"><span class="text-lg"><?php echo currency2html($_smarty_tpl->tpl_vars['scope']->value['currency']);?>
<?php echo $_smarty_tpl->tpl_vars['scope']->value['rate'];?>
</span>/night</p>
                        </div>
                    </div>
                </header>
                <div class="row">
                    <div class="col-md-7">
                        <div class="tabbable booking-details-tabbable">
                            <ul class="nav nav-tabs" id="myTab">
                                <li class="active">
                                  <a href="#rental-photos" data-toggle="tab"><i class="fa fa-camera"></i>Photos</a>
                                </li>
                                <li>
                                  <a href="#rental-map" data-toggle="tab"><i class="fa fa-map-marker"></i>On the Map</a>
                                </li>
                                <?php if (($_smarty_tpl->tpl_vars['scope']->value['calendar'])) {?>
                                <li>
                                  <a href="#rental-calendar" data-toggle="tab"><i class="fa fa-calendar"></i>Calendar</a>
                                </li>
                                <?php }?>
                            </ul>
                            <div class="tab-content">
                                <div class="tab-pane fade in active" id="rental-photos">
                                    <div class="fotorama" data-allowfullscreen="true" data-nav="thumbs">
                                        <?php  $_smarty_tpl->tpl_vars['image'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['image']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['images']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['image']->key => $_smarty_tpl->tpl_vars['image']->value) {
$_smarty_tpl->tpl_vars['image']->_loop = true;
?>
                                          <img src="<?php echo $_smarty_tpl->tpl_vars['image']->value['src'];?>
" alt="<?php echo $_smarty_tpl->tpl_vars['image']->value['title'];?>
" title="<?php echo $_smarty_tpl->tpl_vars['image']->value['title'];?>
" />
                                        <?php } ?>
                                    </div>
                                </div>
                                <div class="tab-pane fade" id="rental-map">
                                    <div id="map-canvas" data-lat=<?php echo $_smarty_tpl->tpl_vars['scope']->value['location_lat'];?>
 data-lng=<?php echo $_smarty_tpl->tpl_vars['scope']->value['location_long'];?>
 style="width:100%; height:500px;"></div>
                                </div>
                                <?php if (($_smarty_tpl->tpl_vars['scope']->value['calendar'])) {?>                                
                                <div class="tab-pane fade" id="rental-calendar">
                                    <?php echo $_smarty_tpl->getSubTemplate ("_calendar.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                                </div>
                                <?php }?>
                            </div>
                        </div>
                    </div>
                    <div class="col-md-5">
                        <?php if (($_smarty_tpl->tpl_vars['scope']->value['review_nr']>0)) {?>
                        <div class="booking-item-meta">
                            <!--h2 class="lh1em mt40">Exceptional!</h2>
                            <h3><?php echo round((($_smarty_tpl->tpl_vars['scope']->value['review_recommend']/$_smarty_tpl->tpl_vars['scope']->value['review_nr'])*100));?>
 % <small >of guests recommend</small></h3-->
                            <div class="booking-item-rating">
                                <input type="number" readonly class="rating" 
                                       value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['review_score'];?>
" 
                                       min=0 max=10
                                       data-rtl="false" data-glyphicon="false" data-show-clear="false"                                       
                                       data-show-caption="false">
                                       
                                <span class="booking-item-rating-number"><b ><?php echo round(($_smarty_tpl->tpl_vars['scope']->value['review_score']/2),"1");?>
</b> of 5 <small class="text-smaller">guest rating</small></span>
                                <p><a class="text-default" href="#">based on <?php echo $_smarty_tpl->tpl_vars['scope']->value['review_nr'];?>
 reviews</a>
                                </p>
                            </div>
                        </div>
                        <?php } else { ?>
                        <div class="gap"></div>
                        <?php }?>
                        <div class="booking-item-dates-change">
                            <form id="booking-form" class="ajax-submit" data-handler="rental-booking">
                                <input type="hidden" name="guest_id" value="<?php echo $_smarty_tpl->tpl_vars['user']->value['id'];?>
">                                                     
                                <input type="hidden" name="site_id" value="<?php echo $_smarty_tpl->tpl_vars['site']->value['id'];?>
">                                                     
                                <input type="hidden" name="apt_id" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['id'];?>
">                                                     
                                <input type="hidden" name="t" value="<?php echo $_smarty_tpl->tpl_vars['scope']->value['property_type'];?>
">                                                     
                                <input type="hidden" name="ng" value="<?php echo $_GET['ng'];?>
">                                                     
                                <div class="input-daterange" data-date-format="MM d, DD">
                                    <div class="row">
                                        <div class="col-md-6">
                                            <div class="form-group form-group-icon-left"><i class="fa fa-calendar input-icon"></i>
                                                <label>Check in</label>
                                                <input type="text" value="<?php echo $_GET['in_disp'];?>
" class="form-control datepicker hasDatepicker" id="in_disp" name="in_disp" placeholder="Checkin" data-dependent_field="out" autocomplete="off">
                                                <input type="hidden" value="<?php echo $_GET['in'];?>
" id="in" name="in">                     
                                            </div>
                                        </div>
                                        <div class="col-md-6">
                                            <div class="form-group form-group-icon-left"><i class="fa fa-calendar input-icon"></i>
                                                <label>Check out</label>
                                                <input type="text" value="<?php echo $_GET['out_disp'];?>
" class="form-control datepicker datepicker-2 hasDatepicker" id="out_disp" name="out_disp" placeholder="Checkout" autocomplete="off">
                                                <input type="hidden" value="<?php echo $_GET['out'];?>
" id="out" name="out">                                                     
                                            </div>                                                                        
                                        </div>                                                                                                                                          
                                    </div>
                                </div>
                                <div class="row">
                                    <div class="col-md-6">
                                        <div class="form-group form-group-icon-left form-group-select-plus">
                                            <label>Guests</label>
                                            <div class="btn-group btn-group-select-num<?php if (($_GET['ng']>=4)) {?> hidden<?php }?>" data-toggle="buttons">
                                                <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['name'] = 'ng';
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] = is_array($_loop=4) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total']);
?>
                                                  <label class="btn btn-primary<?php if (($_GET['ng']==$_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'])) {?> active<?php }?>"><input type="radio" name="options" />
                                                  <?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>

                                                  </label>
                                                <?php endfor; endif; ?>                                            
                                                <label class="btn btn-primary"><input type="radio" name="options" />4+</label>
                                            </div>
                                            <select name="ng" class="form-control<?php if (($_GET['ng']<4)) {?> hidden<?php }?>">
                                                <?php if (isset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng'])) unset($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['name'] = 'ng';
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] = is_array($_loop=15) ? count($_loop) : max(0, (int) $_loop); unset($_loop);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] = ((int) 1) == 0 ? 1 : (int) 1;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = true;
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'];
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] < 0)
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = max($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? 0 : -1, $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']);
else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] = min($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop']-1);
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']) {
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = min(ceil(($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'] > 0 ? $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['loop'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'] : $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start']+1)/abs($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'])), $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['max']);
    if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] == 0)
        $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show'] = false;
} else
    $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'] = 0;
if ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['show']):

            for ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['start'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] = 1;
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] <= $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total'];
                 $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] += $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'], $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration']++):
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['rownum'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_prev'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] - $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index_next'] = $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['index'] + $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['step'];
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['first']      = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == 1);
$_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['last']       = ($_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['iteration'] == $_smarty_tpl->tpl_vars['smarty']->value['section']['ng']['total']);
?>
                                                  <option<?php if (($_GET['ng']==$_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'])) {?> selected="selected"<?php }?>><?php echo $_smarty_tpl->getVariable('smarty')->value['section']['ng']['index'];?>
</option>
                                                <?php endfor; endif; ?>                                            
                                            </select>
                                        </div>
                                    </div>
                                </div>
                                <div class="gap gap-small"></div>	
                                
                                <?php if (($_smarty_tpl->tpl_vars['scope']->value['book_direct'])) {?>
                                <input type="hidden" name="type" value="<?php echo @constant('RES_TYPE_DIRECT');?>
">                                                     
                                <input type="submit" class="btn btn-success btn-lg" value="Book now">
                                
                                <?php } else { ?>
                                <input type="hidden" name="type" value="<?php echo @constant('RES_TYPE_REQUEST');?>
">                                                     
                                <input type="submit" class="btn btn-success btn-lg" value="Request to Book">
                                <?php }?>
                                
                                <a href="#" class="btn btn-primary btn-lg submit-parent" role="button"  data-set_form_input="type" data-value="<?php echo @constant('RES_TYPE_INQUIRY');?>
">Contact Host</a>
                                <!--input type="submit" class="btn btn-primary btn-lg" value="Contact Host"-->
                                
                                <?php if (($_smarty_tpl->tpl_vars['scope']->value['edit_link'])) {?>
                                <a href="<?php echo $_smarty_tpl->tpl_vars['scope']->value['edit_link'];?>
" type="submit" class="btn btn-danger btn-lg">Edit</a>
                                <?php }?>
                            </form>
                        </div>
                    </div>
                </div>
                <div class="gap"></div>
                <div class="row">
                    <div class="col-md-6">
                        <h3>Amenities</h3>
                        <ul class="booking-item-features booking-item-features-expand-inline  mb30 clearfix">
                        <?php  $_smarty_tpl->tpl_vars['fac'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['fac']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['facs']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['fac']->key => $_smarty_tpl->tpl_vars['fac']->value) {
$_smarty_tpl->tpl_vars['fac']->_loop = true;
?>
                            <li class="col-xs-6 col-sm-4 col-md-6 col-lg-4"><i class="<?php echo $_smarty_tpl->tpl_vars['fac']->value['icon'];?>
" id="fac_<?php echo $_smarty_tpl->tpl_vars['fac']->value['id'];?>
"></i><span class="booking-item-feature-title"><?php echo $_smarty_tpl->tpl_vars['fac']->value['name'];?>
</span></li>
                        <?php } ?>
                        </ul>
                    </div>
                    <div class="col-md-6">
                        <h3>Property description</h3>
                        <?php echo $_smarty_tpl->tpl_vars['scope']->value['description'];?>
                          
                    </div>
                </div>
                <div class="gap gap-small"></div>
                <h3 class="mb20"><?php echo $_smarty_tpl->tpl_vars['scope']->value['review_nr'];?>
 Property Review<?php if (($_smarty_tpl->tpl_vars['scope']->value['review_nr']!=1)) {?>s<?php }?></h3>
                <div class="row row-wrap">
                    <div class="col-md-8">
                        <ul class="booking-item-reviews list">
                        <?php if (($_smarty_tpl->tpl_vars['scope']->value['review_nr']>0)) {?>
                          <?php  $_smarty_tpl->tpl_vars['review'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['review']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['reviews']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['review']->key => $_smarty_tpl->tpl_vars['review']->value) {
$_smarty_tpl->tpl_vars['review']->_loop = true;
?>
                            <li>
                            <?php echo $_smarty_tpl->getSubTemplate ("_rental-review-item.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array('compact'=>'1'), 0);?>

                            </li>
                          <?php } ?>
                        <?php } else { ?>
                        <li>No reviews yet.</li>
                        <?php }?>
                        </ul>
                        <?php if (($_smarty_tpl->tpl_vars['scope']->value['review_nr']>0)) {?>
                        <div class="row wrap">
                            <div class="col-md-5">
                                <p><small><?php echo $_smarty_tpl->tpl_vars['scope']->value['review_nr'];?>
 review<?php if (($_smarty_tpl->tpl_vars['scope']->value['review_nr']!=1)) {?>s<?php }?> on this property. &nbsp;&nbsp;Showing 1 to 7</small>
                                </p>
                            </div>
                            <div class="col-md-7">
                                <ul class="pagination">
                                    <li class="active"><a href="#">1</a>
                                    </li>
                                    <li><a href="#">2</a>
                                    </li>
                                    <li><a href="#">3</a>
                                    </li>
                                    <li><a href="#">4</a>
                                    </li>
                                    <li><a href="#">5</a>
                                    </li>
                                    <li><a href="#">6</a>
                                    </li>
                                    <li><a href="#">7</a>
                                    </li>
                                    <li class="dots">...</li>
                                    <li><a href="#">43</a>
                                    </li>
                                    <li class="next"><a href="#">Next Page</a>
                                    </li>
                                </ul>
                            </div>
                        </div>
                        <div class="gap gap-small"></div>
                        <?php }?>
                        
                    </div>
                    <?php if (($_smarty_tpl->tpl_vars['scope']->value['nearby_golf'])) {?>
                    <div class="col-md-4">
                        <h4>Nearby golf courses</h4>
                        <ul class="booking-list">
                            <?php  $_smarty_tpl->tpl_vars['golf'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['golf']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['nearby_golf']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['golf']->key => $_smarty_tpl->tpl_vars['golf']->value) {
$_smarty_tpl->tpl_vars['golf']->_loop = true;
?>
                            <li>
                              <a href="/golf-club/<?php echo $_smarty_tpl->tpl_vars['golf']->value['id'];?>
<?php echo $_smarty_tpl->tpl_vars['query_string']->value;?>
">
                              <?php echo $_smarty_tpl->getSubTemplate ("_golf-club-nearby.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                              </a>
                            </li>
                            <?php } ?>
                        </ul>
                        
                        <h4>Nearby properties</h4>
                        <ul class="booking-list">
                            <?php  $_smarty_tpl->tpl_vars['apt'] = new Smarty_Variable; $_smarty_tpl->tpl_vars['apt']->_loop = false;
 $_from = $_smarty_tpl->tpl_vars['scope']->value['nearby_apts']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array');}
foreach ($_from as $_smarty_tpl->tpl_vars['apt']->key => $_smarty_tpl->tpl_vars['apt']->value) {
$_smarty_tpl->tpl_vars['apt']->_loop = true;
?>
                            <li>
                                <a href="<?php echo smarty_property_link($_smarty_tpl->tpl_vars['apt']->value['id']);?>
<?php echo $_smarty_tpl->tpl_vars['query_string']->value;?>
">
                                <?php echo $_smarty_tpl->getSubTemplate ("_rental-nearby.html", $_smarty_tpl->cache_id, $_smarty_tpl->compile_id, 0, null, array(), 0);?>

                                </a>
                            </li>
                            <?php } ?>
                        </ul>
                    </div>
                    <?php }?>
                    
                </div>
            </div>
            <div class="gap gap-small"></div>
        </div>


<?php }} ?>
