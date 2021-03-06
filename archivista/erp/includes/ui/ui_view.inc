<?php

include_once($path_to_root . "/admin/db/voiding_db.inc");
include_once($path_to_root . "/includes/types.inc");

//--------------------------------------------------------------------------------------

function get_supplier_trans_view_str($type, $trans_no, $label="")
{
  global $path_to_root, $use_popup_windows;

  $viewer = "";
  if ($type == systypes::po())
    $viewer = "view_po.php";
  elseif ($type == 20)
    $viewer = "view_supp_invoice.php";
  elseif ($type == 21)
    $viewer = "view_supp_credit.php";
  elseif ($type == 22)
    $viewer = "view_supp_payment.php";
  elseif ($type == 25)
    $viewer = "view_grn.php";
  else
    return null;

  if ($label == "")
    $label = $trans_no;

  if ($viewer != "")
  {
    if ($use_popup_windows)
      $preview_str = "<a target='_blank' href='$path_to_root/purchasing/view/$viewer?trans_no=$trans_no' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$label</a>";
    else
      $preview_str = "<a target='_blank' href='$path_to_root/purchasing/view/$viewer?trans_no=$trans_no'>$label</a>";
  }
  else
    $preview_str = $label;

  return $preview_str;
}

//--------------------------------------------------------------------------------------

function get_gl_view_str($type, $trans_no, $label="", $force=false)
{
  global $path_to_root, $use_popup_windows;

  if (!$force && !user_show_gl_info())
    return "";

  if ($label == "")
    $label = tr("GL");
  if ($use_popup_windows)
    $gl_view = "<a target='_blank' href='$path_to_root/gl/view/gl_trans_view.php?type_id=$type&trans_no=$trans_no' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$label</a>";
  else
    $gl_view = "<a target='_blank' href='$path_to_root/gl/view/gl_trans_view.php?type_id=$type&trans_no=$trans_no'>$label</a>";

  return $gl_view;
}

//--------------------------------------------------------------------------------------

function get_gl_view_str_cell($type, $trans_no, $label="")
{
  $str = get_gl_view_str($type, $trans_no, $label);
  if ($str != "")
    return "<td>$str</td>";
}

//--------------------------------------------------------------------------------------

function get_customer_trans_view_str($type, $trans_no, $label="")
{
  global $path_to_root, $use_popup_windows;

  $viewer = "";
  if ($type == 10)
    $viewer = "view_invoice.php";
  elseif ($type == 11)
    $viewer = "view_credit.php";
  elseif ($type == 12)
    $viewer = "view_receipt.php";
  elseif ($type == 13)
    $viewer = "view_dispatch.php";
  elseif ($type == 30)
    $viewer = "view_sales_order.php";
  else
    return null;

  if(!is_array($trans_no)) $trans_no = array($trans_no);

  $lbl = $label;
  $preview_str = '';
  foreach($trans_no as $trans) {
  if ($label == "")
    $lbl = $trans;

  if($preview_str!='') $preview_str .= ',';

  if ($viewer != "")
  {
    if ($use_popup_windows)
      $preview_str .= "<a target='_blank' href='$path_to_root/sales/view/$viewer?trans_no=$trans' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$lbl</a>";
    else
      $preview_str .= "<a target='_blank' href='$path_to_root/sales/view/$viewer?trans_no=$trans'>$lbl</a>";
  }
  else
    $preview_str .= $lbl;
  }

  return $preview_str;
}

//--------------------------------------------------------------------------------------

function get_banking_trans_view_str($type, $trans_no, $label="")
{
  global $path_to_root, $use_popup_windows;

  $viewer = "";

  if ($type == 4)
    $viewer = "bank_transfer_view.php";
  elseif ($type == 1)
    $viewer = "gl_payment_view.php";
  elseif ($type == 2)
    $viewer = "gl_deposit_view.php";
  elseif ($type == 0)
    $viewer = "";
  else
    return null;

  if ($label == "")
    $label = $trans_no;

  if ($viewer != "")
  {
    if ($use_popup_windows)
      $preview_str = "<a target='_blank' href='$path_to_root/gl/view/$viewer?trans_no=$trans_no' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$label</a>";
    else
      $preview_str = "<a target='_blank' href='$path_to_root/gl/view/$viewer?trans_no=$trans_no'>$label</a>";
  }
  else
    $preview_str = $label;

  return $preview_str;
}

//--------------------------------------------------------------------------------------

function get_inventory_trans_view_str($type, $trans_no, $label="")
{
  global $path_to_root, $use_popup_windows;

  $viewer = "";

  if ($type == systypes::inventory_adjustment())
    $viewer = "view_adjustment.php";
  elseif ($type == systypes::location_transfer())
    $viewer = "view_transfer.php";
  else
    return null;

  if ($label == "")
    $label = $trans_no;

  if ($viewer != "")
  {
    if ($use_popup_windows)
      $preview_str = "<a target='_blank' href='$path_to_root/inventory/view/$viewer?trans_no=$trans_no' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$label</a>";
    else
      $preview_str = "<a target='_blank' href='$path_to_root/inventory/view/$viewer?trans_no=$trans_no'>$label</a>";
  }
  else
    $preview_str = $label;

  return $preview_str;
}

//--------------------------------------------------------------------------------------

function get_manufacturing_trans_view_str($type, $trans_no, $label="")
{
  global $path_to_root, $use_popup_windows;

  $viewer = "";

  if ($type == 28)
    $viewer = "wo_issue_view.php";
  elseif ($type == 29)
    $viewer = "wo_production_view.php";
  elseif ($type == systypes::work_order())
    $viewer = "work_order_view.php";
  else
    return null;

  if ($label == "")
    $label = $trans_no;

  if ($viewer != "")
  {
    if ($use_popup_windows)
      $preview_str = "<a target='_blank' href='$path_to_root/manufacturing/view/$viewer?trans_no=$trans_no' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$label</a>";
    else
      $preview_str = "<a target='_blank' href='$path_to_root/manufacturing/view/$viewer?trans_no=$trans_no'>$label</a>";
  }
  else
    $preview_str = $label;

  return $preview_str;
}

//--------------------------------------------------------------------------------------

function get_dimensions_trans_view_str($type, $trans_no, $label="")
{
  global $path_to_root, $use_popup_windows;

  $viewer = "";

  if ($type == 40)
    $viewer = "view_dimension.php";
  else
    return null;

  if ($label == "")
    $label = $trans_no;

  if ($viewer != "")
  {
    if ($use_popup_windows)
      $preview_str = "<a target='_blank' href='$path_to_root/dimensions/view/$viewer?trans_no=$trans_no' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$label</a>";
    else
      $preview_str = "<a target='_blank' href='$path_to_root/dimensions/view/$viewer?trans_no=$trans_no'>$label</a>";
  }
  else
    $preview_str = $label;

  return $preview_str;
}

//--------------------------------------------------------------------------------------

function get_trans_view_str($type, $trans_no, $label="")
{
  $view_str = get_customer_trans_view_str($type, $trans_no, $label);
  if ($view_str != null)
    return $view_str;

  $view_str = get_supplier_trans_view_str($type, $trans_no, $label);
  if ($view_str != null)
    return $view_str;

  $view_str = get_banking_trans_view_str($type, $trans_no, $label);
  if ($view_str != null)
    return $view_str;

  $view_str = get_inventory_trans_view_str($type, $trans_no, $label);
  if ($view_str != null)
    return $view_str;

  $view_str = get_manufacturing_trans_view_str($type, $trans_no, $label);
  if ($view_str != null)
    return $view_str;

  $view_str = get_dimensions_trans_view_str($type, $trans_no, $label);
  if ($view_str != null)
    return $view_str;

  return null;
}

//--------------------------------------------------------------------------------------

function exchange_rate_display($from_currency, $to_currency, $date_, $buttons=true)
{
  if ($from_currency != $to_currency)
  {
    if ($buttons && isset($_POST['get_rate']))
    {
      $comp_currency = get_company_currency();
      if ($from_currency == $comp_currency)
        $currency = $to_currency;
      else
        $currency = $from_currency;
      $rate = get_ecb_rate($currency);
      if (get_date_exchange_rate($currency, $date_))
        update_exchange_rate($currency, $date_, $rate, $rate);
      else
        add_exchange_rate($currency, $date_, $rate, $rate);
      if ($from_currency == $comp_currency)
        $rate = 1 / $rate;
    }
    else
      $rate = get_exchange_rate_from_to($to_currency, $from_currency, $date_);
    $rate = number_format2($rate, user_exrate_dec());
      label_row(tr("Exchange Rate:"),"1 " . $from_currency . " = " .  $rate . " " . $to_currency .
      ($buttons?"  " . submit('get_rate',tr("Get"), false):""));
  }
}

//--------------------------------------------------------------------------------------

function is_voided_display($type, $id, $label)
{
  global $table_style;
  $void_entry = get_voided_entry($type, $id);

  if ($void_entry == null)
    return false;

  start_table("width=50% $table_style");
  echo "<tr><td align=center><font color=red>$label</font><br>";
  echo "<font color=red>" . tr("Date Voided:") . " " . sql2date($void_entry["date_"]) . "</font><br>";
  if (strlen($void_entry["memo_"]) > 0)
    echo "<center><font color=red>" . tr("Memo:") . " " . $void_entry["memo_"] . "</font><br>";
  echo "</td></tr>";
  end_table(1);

  return true;
}

//--------------------------------------------------------------------------------------

function comments_display_row($type, $id)
{
  $comments = get_comments($type, $id);
  if ($comments and db_num_rows($comments))
  {
    echo "<tr><td colspan=15>";
      while ($comment = db_fetch($comments))
      {
        echo $comment["memo_"] . "<br>";
      }
    echo "</td></tr>";
  }
}

//--------------------------------------------------------------------------------------

function get_comments_string($type, $type_no)
{
  $str_return = "";
  $result = get_comments($type, $type_no);
  while ($comment = db_fetch($result))
  {
    if (strlen($str_return))
      $str_return = $str_return . " \n";
    $str_return = $str_return . $comment["memo_"];
  }
  return $str_return;
}

//--------------------------------------------------------------------------------------

function view_stock_status($stock_id, $description=null)
{
  global $path_to_root;
  if ($description)
    //hyperlink_params_separate($path_to_root . "/inventory/inquiry/stock_status.php", (user_show_codes()?$stock_id . " - ":"") . $description, "stock_id=$stock_id");
    $preview_str = "<a target='_blank' href='$path_to_root/inventory/inquiry/stock_status.php?stock_id=$stock_id' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >". (user_show_codes()?$stock_id . " - ":"") . $description."</a>";
  else
    //hyperlink_params_separate($path_to_root . "/inventory/inquiry/stock_status.php", $stock_id, "stock_id=$stock_id");
    $preview_str = "<a target='_blank' href='$path_to_root/inventory/inquiry/stock_status.php?stock_id=$stock_id' onclick=\"javascript:openWindow(this.href,this.target); return false;\" >$stock_id</a>";
  echo $preview_str;
}

function view_stock_status_cell($stock_id, $description=null)
{
  echo "<td>";
  view_stock_status($stock_id, $description);
  echo "</td>";
}

//--------------------------------------------------------------------------------------

function display_debit_or_credit_cells($value)
{
  if ($value > 0)
  {
    amount_cell($value);
    label_cell("");
  }
  elseif ($value < 0)
  {
    label_cell("");
    amount_cell(abs($value));
  }
  else
  {
    //label_cell("");
    amount_cell(0);
    label_cell("");
  }
}

//--------------------------------------------------------------------------------------

function display_customer_trans_tax_details($tax_items, $columns)
{
    while ($tax_item = db_fetch($tax_items))
    {
      $tax = number_format2($tax_item['amount'],user_price_dec());
      if ($tax_item['included_in_price'])
          label_row(tr("Included") . " " . $tax_item['tax_type_name'] . " (" . $tax_item['rate'] . "%) " .
            tr("Amount") . ": $tax", "", "colspan=$columns align=right", "align=right");
      else
          label_row($tax_item['tax_type_name'] . " (" . $tax_item['rate'] . "%)",
            $tax, "colspan=$columns align=right", "align=right");
    }
}

//--------------------------------------------------------------------------------------

function display_supp_trans_tax_details($tax_items, $columns)
{
    while ($tax_item = db_fetch($tax_items))
    {
      $tax = number_format2(abs($tax_item['amount']),user_price_dec());
      if ($tax_item['included_in_price'])
          label_row(tr("Included") . " " . $tax_item['tax_type_name'] . " (" . $tax_item['rate'] . "%) " .
            tr("Amount:") . ": $tax", "colspan=$columns align=right", "align=right");
      else
          label_row($tax_item['tax_type_name'] . " (" . $tax_item['rate'] . "%)",
            $tax, "colspan=$columns align=right", "align=right");
    }
}

//--------------------------------------------------------------------------------------

function display_edit_tax_items($taxes, $columns, $tax_included, $leftspan=0)
{
  $total = 0;

    foreach ($taxes as $taxitem)
    {
      if ($tax_included)
      {
          label_row(tr("Included") . " " . $taxitem['tax_type_name'] . " (" . $taxitem['rate'] . "%) " .
            tr("Amount:") . " " . number_format2($taxitem['Value'],user_price_dec()), "", "colspan=$columns align=right", "align=right",$leftspan);
      }
      else
      {
          label_row($taxitem['tax_type_name'] . " (" . $taxitem['rate'] . "%)",
            number_format2($taxitem['Value'],user_price_dec()), "colspan=$columns align=right", "align=right",$leftspan);
          $total +=  $taxitem['Value'];
      }
    }

    return $total;
}

//--------------------------------------------------------------------------------------

function display_footer_exit()
{
  global $path_to_root;
  br(2);
  end_page();
  exit;
}

//--------------------------------------------------------------------------------------

function display_allocations($alloc_result, $total)
{
  global $table_style;

  if (!$alloc_result || db_num_rows($alloc_result) == 0)
    return;

    display_heading2(tr("Allocations"));

    start_table("$table_style width=80%");

    $th = array( tr("Type"), tr("Number"), tr("Date"), tr("Total Amount"),
      tr("Left to Allocate"), tr("This Allocation"));
  table_header($th);
    $k = $total_allocated = 0;

    while ($alloc_row = db_fetch($alloc_result))
    {

      alt_table_row_color($k);

      label_cell(systypes::name($alloc_row['type']));
      label_cell(get_trans_view_str($alloc_row['type'],$alloc_row['trans_no']));
      label_cell(sql2date($alloc_row['tran_date']));
      amount_cell($alloc_row['Total']);
      //amount_cell($alloc_row['Total'] - $alloc_row['PrevAllocs'] - $alloc_row['amt']);
      amount_cell($alloc_row['Total'] - $alloc_row['amt']);
      amount_cell($alloc_row['amt']);
      end_row();

      $total_allocated += $alloc_row['amt'];
    }
    start_row();
     label_cell(tr("Total Allocated:"), "align=right colspan=5");
  amount_cell($total_allocated);
  end_row();
  start_row();
    label_cell(tr("Left to Allocate:"), "align=right colspan=5");
    amount_cell($total - $total_allocated);
    end_row();

    end_table(1);
}

//--------------------------------------------------------------------------------------

function display_allocations_from($person_type, $person_id, $type, $type_no, $total)
{
  switch ($person_type)
  {
    case payment_person_types::customer() :
      $alloc_result = get_allocatable_to_cust_transactions($person_id, $type_no, $type);
      display_allocations($alloc_result, $total);
      return;
    case payment_person_types::supplier() :
      $alloc_result = get_allocatable_to_supp_transactions($person_id, $type_no, $type);
      display_allocations($alloc_result, $total);
      return;
  }
}

function get_js_go_back()
{
  $js = "\n<script type=\"text/javascript\">\n"
     . "<!--\n"
    . "function goBack()\n"
    . "{\n"
    . "  if (window.history.length <= 1)\n"
    . "   window.close();\n"
    . "  else\n"
    . "   window.history.go(-1);\n"
    . "}\n"
    . "-->\n"
    . "</script>\n";
  return $js;
}

function get_js_open_window($width, $height)
{
  $js = "\n<script type=\"text/javascript\">\n"
     . "<!--\n"
    . "function openWindow(url, title)\n"
    . "{\n"
    . " var left = (screen.width - $width) / 2;\n"
    . " var top = (screen.height - $height) / 2;\n"
    . " window.open(url, title, 'width=$width,height=$height,left='+left+',top='+top+',screenX='+left+',screenY='+top+',status=no,scrollbars=yes');\n"
    . "}\n"
    . "-->\n"
    . "</script>\n";
  return $js;
}

//$focus_on = array();
/*
  Setting focus on element $name in $form.
  If $form<0 $name is element id.
*/
function set_focus($name, $form_no=0) {
//  global $focus_on;
//  $focus_on['name'] = $name;
//  $focus_on['form'] = $form_no;
    $_POST['_focus'] = $name;
}
//
//  Set default focus on first field $name if not set yet
//
function default_focus($name, $form_no=0) {
//  global $focus_on;
//    if (!isset($focus_on['name']) && (!isset($_POST['_focus']) || $_POST['_focus']=='') ) {
//echo "<h2>$name</h2>";
//  $focus_on['name'] = $name;
//  $focus_on['form'] = $form_no;
//    }
    if (!isset($_POST['_focus'])) {
  $_POST['_focus'] = $name;
    }
}
/*
function set_js_focus() {
  global $focus_on;
  $js = '';

//  if (isset($focus_on['name'])) {

    $js =  "<script type=\"text/javascript\">\n"
  ."Behaviour.addLoadEvent(function(){ setFocus('".$focus_on['name']."'".( $focus_on['form']>=0 ?  (",".$focus_on['form']): '').
  ");});"
  ."</script>";
//  }
  return $js;
}
*/
function get_js_png_fix()
{
  $js = "<script type=\"text/javascript\">\n"
    . "function fixPNG(myImage)\n"
    . "{\n"
    . " var arVersion = navigator.appVersion.split(\"MSIE\")\n"
    . " var version = parseFloat(arVersion[1])\n"
      . " if ((version >= 5.5) && (version < 7) && (document.body.filters))\n"
      . " {\n"
         . "  var imgID = (myImage.id) ? \"id='\" + myImage.id + \"' \" : \"\"\n"
       . "  var imgClass = (myImage.className) ? \"class='\" + myImage.className + \"' \" : \"\"\n"
       . "  var imgTitle = (myImage.title) ?\n"
    . "    \"title='\" + myImage.title  + \"' \" : \"title='\" + myImage.alt + \"' \"\n"
       . "  var imgStyle = \"display:inline-block;\" + myImage.style.cssText\n"
       . "  var strNewHTML = \"<span \" + imgID + imgClass + imgTitle\n"
        . "    + \" style=\\\"\" + \"width:\" + myImage.width\n"
        . "    + \"px; height:\" + myImage.height\n"
        . "    + \"px;\" + imgStyle + \";\"\n"
        . "    + \"filter:progid:DXImageTransform.Microsoft.AlphaImageLoader\"\n"
        . "    + \"(src=\'\" + myImage.src + \"\', sizingMethod='scale');\\\"></span>\"\n"
       . "  myImage.outerHTML = strNewHTML\n"
      . " }\n"
    . "}\n"
    . "</script>\n";
  return $js;
}

function get_js_date_picker()
{
  global $js_date_picker;
  $js = "<style>
#CCIFrame { display: none; left: 0px; position: absolute; top: 0px; height: 250px; width: 250px; z-index: 99;}
#CC { position:absolute; background-color:#FFF; margin:0; padding:0; display:none; z-index: 100;}
#CC table { font-family: arial, verdana, helvetica, sans-serif;font-size: 8pt; border-left: 1px solid #336; border-right: 1px solid #336;}
#CC th { font-weight: normal;}
#CC th a { font-weight: normal; text-decoration: none; color: #FFF; padding: 1px;}
#CC td { text-align: center;}
#CC .header { background-color: #336;}
#CC .weekday { background-color: #DDD; color: #000;}
#CC .weekend { background-color: #FFC; color: #000;}
#CC .current { border: 1px solid #339; background-color: #336; color: #FFF;}
#CC .weekday,#CC .weekend,#CC .current { display: block; text-decoration: none; border: 1px solid #FFF; width: 2em;}
#CC .weekday:hover,#CC .weekend:hover,#CC .current:hover { color: #FFF; background-color: #336; border: 1px solid #999;}
#CC .previous { text-align: left;}
#CC .next { text-align: right;}
#CC .previous,#CC .next { padding: 1px 3px 1px 3px; font-size: 1.4em;}
#CC .previous a,#CC .next a { color: #FFF; text-decoration: none; font-weight: bold;}
#CC .title { text-align: center; font-weight: bold; color: #FFF;}
#CC .empty { background-color: #CCC; border: 1px solid #FFF;}
</style>
";
  global $dateseps, $date_system;

  $how = user_date_format();        // 0 = us/ca, 1 = eu, au, nz, 2 = jp, sw
  $sep = $dateseps[user_date_sep()];    // date separator
  $wstart = (($date_system == 1 || $date_system == 2) ? 6 : ($how == 0 ? 0 : 1));      // weekstart (sun = 0, mon = 1)
  $months = array(tr("January"),tr("February"),tr("March"),tr("April"),tr("May"),tr("June"),tr("July"),tr("August"),tr("September"),tr("October"),tr("November"),tr("December"));
  $wdays = array(tr("Su"),tr("Mo"),tr("Tu"),tr("We"),tr("Th"),tr("Fr"),tr("Sa"));
  $back = tr("Back");
  if ($date_system == 1)
    list($cyear, $cmon, $cday) = gregorian_to_jalali(date("Y"), date("n"), date("j"));
  else if ($date_system == 2)
    list($cyear, $cmon, $cday) = gregorian_to_islamic(date("Y"), date("n"), date("j"));
  
	add_js_source($js);

  $js = "
function positionInfo(object) {
  var p_elm = object;
  this.getElementLeft = getElementLeft;
  function getElementLeft() {
    var x = 0;
    var elm;
    if(typeof(p_elm) == 'object'){
      elm = p_elm;
    } else {
      elm = document.getElementById(p_elm);
    }
    while (elm != null) {
      x+= elm.offsetLeft;
      elm = elm.offsetParent;
    }
    return parseInt(x);
  }
  this.getElementWidth = getElementWidth;
  function getElementWidth(){
    var elm;
    if(typeof(p_elm) == 'object'){
      elm = p_elm;
    } else {
      elm = document.getElementById(p_elm);
    }
    return parseInt(elm.offsetWidth);
  }
  this.getElementRight = getElementRight;
  function getElementRight(){
    return getElementLeft(p_elm) + getElementWidth(p_elm);
  }
  this.getElementTop = getElementTop;
  function getElementTop() {
    var y = 0;
    var elm;
    if(typeof(p_elm) == 'object'){
      elm = p_elm;
    } else {
      elm = document.getElementById(p_elm);
    }
    while (elm != null) {
      y+= elm.offsetTop;
      elm = elm.offsetParent;
    }
    return parseInt(y);
  }
  this.getElementHeight = getElementHeight;
  function getElementHeight(){
    var elm;
    if(typeof(p_elm) == 'object'){
      elm = p_elm;
    } else {
      elm = document.getElementById(p_elm);
    }
    return parseInt(elm.offsetHeight);
  }
  this.getElementBottom = getElementBottom;
  function getElementBottom(){
    return getElementTop(p_elm) + getElementHeight(p_elm);
  }
}
function CC() {
  var calendarId = 'CC';
  var currentYear = 0;
  var currentMonth = 0;
  var currentDay = 0;
  var selectedYear = 0;
  var selectedMonth = 0;
  var selectedDay = 0;
  var months = ['$months[0]','$months[1]','$months[2]','$months[3]','$months[4]','$months[5]','$months[6]','$months[7]','$months[8]','$months[9]','$months[10]','$months[11]'];
  var wdays = ['$wdays[0]', '$wdays[1]', '$wdays[2]', '$wdays[3]', '$wdays[4]', '$wdays[5]', '$wdays[6]'];
  var dateField = null;
  function getProperty(p_property){
    var p_elm = calendarId;
    var elm = null;
    if(typeof(p_elm) == 'object'){
      elm = p_elm;
    } else {
      elm = document.getElementById(p_elm);
    }
    if (elm != null){
      if(elm.style){
        elm = elm.style;
        if(elm[p_property]){
          return elm[p_property];
        } else {
          return null;
        }
      } else {
        return null;
      }
    }
  }
  function setElementProperty(p_property, p_value, p_elmId){
    var p_elm = p_elmId;
    var elm = null;
    if(typeof(p_elm) == 'object'){
      elm = p_elm;
    } else {
      elm = document.getElementById(p_elm);
    }
    if((elm != null) && (elm.style != null)){
      elm = elm.style;
      elm[ p_property ] = p_value;
    }
  }
  function setProperty(p_property, p_value) {
    setElementProperty(p_property, p_value, calendarId);
  }
  function getDaysInMonth(year, month) {
";
  if ($date_system == 1)
    $js .= "
    return [31,31,31,31,31,31,30,30,30,30,30,(((((((year - ((year > 0) ? 474 : 473)) % 2820) + 474) + 38) * 682) % 2816) < 682 ? 30 : 29)][month-1];
";
  else if ($date_system == 2)
    $js .= "
    return [30,29,30,29,30,29,30,29,30,29,30,(((((11 * year) + 14) % 30) < 11) ? 30 : 29)][month-1];
";
  else
    $js .= "
    return [31,((!(year % 4 ) && ( (year % 100 ) || !( year % 400 ) ))?29:28),31,30,31,30,31,31,30,31,30,31][month-1];
";
  $js .= "
  }
  function getDayOfWeek(year, month, day) {
";
  if ($date_system == 1 || $date_system == 2)
  {
    $js .= "
  function mod(a, b)
  {
      return a - (b * Math.floor(a / b));
  }
  function jwday(j)
  {
      return mod(Math.floor((j + 1.5)), 7);
  }
";
  if ($date_system == 1)
    $js .= "
    var epbase, epyear, t;
    epbase = year - ((year >= 0) ? 474 : 473);
    epyear = 474 + mod(epbase, 2820);
    t = day + ((month <= 7) ? ((month - 1) * 31) : (((month - 1) * 30) + 6)) +
      Math.floor(((epyear * 682) - 110) / 2816) + (epyear - 1) * 365 +
      Math.floor(epbase / 2820) * 1029983 + (1948320.5 - 1);
";
  else if ($date_system == 2)
    $js .= "
  var t;
  t = Math.floor((11 * year + 3) / 30) + 354 * year + 30 * month -
    Math.floor((month - 1) / 2) + day + 1948440 - 385;
";
  $js .= "
    return jwday(t);
";
  }
  else
    $js .= "
    var date = new Date(year,month-1,day)
    return date.getDay();
";
  $js .= "
  }
  this.clearDate = clearDate;
  function clearDate() {
    dateField.value = '';
    hide();
  }
  this.setDate = setDate;
  function setDate(year, month, day) {
    if (dateField) {
      if (month < 10) {month = '0' + month;}
      if (day < 10) {day = '0' + day;}
";
  if ($how == 0)
    $js .= "
      var dateString = month+'$sep'+day+'$sep'+year;
";
  else if ($how == 1)
    $js .= "
      var dateString = day+'$sep'+month+'$sep'+year;
";
  else
    $js .= "
      var dateString = year+'$sep'+month+'$sep'+day;
";
  $js .= "
      dateField.value = dateString;
      hide();
    }
    return;
  }
  this.changeMonth = changeMonth;
  function changeMonth(change) {
    currentMonth += change;
    currentDay = 0;
    if(currentMonth > 12) {
      currentMonth = 1;
      currentYear++;
    } else if(currentMonth < 1) {
      currentMonth = 12;
      currentYear--;
    }
    calendar = document.getElementById(calendarId);
    calendar.innerHTML = calendarDrawTable();
  }
  this.changeYear = changeYear;
  function changeYear(change) {
    currentYear += change;
    currentDay = 0;
    calendar = document.getElementById(calendarId);
    calendar.innerHTML = calendarDrawTable();
  }
  function getCurrentYear() {
    var year = new Date().getYear();
    if(year < 1900) year += 1900;
    return year;
  }
  function getCurrentMonth() {
    return new Date().getMonth() + 1;
  }
  function getCurrentDay() {
    return new Date().getDate();
  }
  function calendarDrawTable() {
    var dayOfMonth = 1;
    var wstart = $wstart;
    var validDay = 0;
    var startDayOfWeek = getDayOfWeek(currentYear, currentMonth, dayOfMonth);
    var daysInMonth = getDaysInMonth(currentYear, currentMonth);
    var css_class = null; //CSS class for each day
    var table = \"<table cellspacing='0' cellpadding='0' border='0'>\";
    table += \"<tr class='header'>\";
    table += \"  <td colspan='2' class='previous'><a href='javascript:changeCCMonth(-1);'>&lt;</a><br><a href='javascript:changeCCYear(-1);'>&laquo;</a></td>\";
    table += \"  <td colspan='3' class='title'>\" + months[currentMonth-1] + \"<br>\" + currentYear + \"</td>\";
    table += \"  <td colspan='2' class='next'><a href='javascript:changeCCMonth(1);'>&gt;</a><br><a href='javascript:changeCCYear(1);'>&raquo;</a></td>\";
    table += \"</tr>\";
    table += \"<tr>\";
    for (var n=0; n<7; n++)
      table += \"<th>\" + wdays[(wstart+n)%7]+\"</th>\";
    table += \"</tr>\";
    for(var week=0; week < 6; week++) {
      table += \"<tr>\";
      for(var n=0; n < 7; n++) {
        dayOfWeek = (wstart+n)%7;
        if(week == 0 && startDayOfWeek == dayOfWeek) {
          validDay = 1;
        } else if (validDay == 1 && dayOfMonth > daysInMonth) {
          validDay = 0;
        }
        if(validDay) {
          if (dayOfMonth == selectedDay && currentYear == selectedYear && currentMonth == selectedMonth) {
            css_class = 'current';
";
  if ($date_system == 1 || $date_system == 2)
    $js .= "
          } else if (dayOfWeek == 5) {
";
  else
    $js .= "
          } else if (dayOfWeek == 0 || dayOfWeek == 6) {
";
    $js .= "
            css_class = 'weekend';
          } else {
            css_class = 'weekday';
          }
          table += \"<td><a class='\"+css_class+\"' href=\\\"javascript:setCCDate(\"+currentYear+\",\"+currentMonth+\",\"+dayOfMonth+\")\\\">\"+dayOfMonth+\"</a></td>\";
          dayOfMonth++;
        } else {
          table += \"<td class='empty'>&nbsp;</td>\";
        }
      }
      table += \"</tr>\";
    }
    table += \"<tr class='header'><th colspan='7' style='padding: 3px;'><a href='javascript:hideCC();'>$back</a></td></tr>\";
    table += \"</table>\";
    return table;
  }
  this.show = show;
  function show(field) {
    can_hide = 0;
    if (dateField == field) {
      return;
    } else {
      dateField = field;
    }
    if(dateField) {
      try {
        var dateString = new String(dateField.value);
        var dateParts = dateString.split('$sep');
";
  if ($how == 0)
    $js .= "
        selectedMonth = parseInt(dateParts[0],10);
        selectedDay = parseInt(dateParts[1],10);
        selectedYear = parseInt(dateParts[2],10);
";
  else if ($how == 1)
    $js .= "
        selectedDay = parseInt(dateParts[0],10);
        selectedMonth = parseInt(dateParts[1],10);
        selectedYear = parseInt(dateParts[2],10);
";
  else
    $js .= "
        selectedYear = parseInt(dateParts[0],10);
        selectedMonth = parseInt(dateParts[1],10);
        selectedDay = parseInt(dateParts[2],10);
";
  $js .= "
      } catch(e) {}
    }
    if (!(selectedYear && selectedMonth && selectedDay)) {
";
  if ($date_system == 1 || $date_system == 2)
  {
    $js .= "
      selectedMonth = $cmon;
      selectedDay = $cday;
      selectedYear = $cyear;
";
  }
  else
  {
    $js .= "
      selectedMonth = getCurrentMonth();
      selectedDay = getCurrentDay();
      selectedYear = getCurrentYear();
";
  }
  $js .= "
    }
    currentMonth = selectedMonth;
    currentDay = selectedDay;
    currentYear = selectedYear;
    if(document.getElementById){
      calendar = document.getElementById(calendarId);
      calendar.innerHTML = calendarDrawTable(currentYear, currentMonth);
      setProperty('display', 'block');
      var fieldPos = new positionInfo(dateField);
      var calendarPos = new positionInfo(calendarId);
      var x = fieldPos.getElementLeft();
      var y = fieldPos.getElementBottom();
      setProperty('left', x + 'px');
      setProperty('top', y + 'px');
      if (document.all) {
        setElementProperty('display', 'block', 'CCIframe');
        setElementProperty('left', x + 'px', 'CCIframe');
        setElementProperty('top', y + 'px', 'CCIframe');
        setElementProperty('width', calendarPos.getElementWidth() + 'px', 'CCIframe');
        setElementProperty('height', calendarPos.getElementHeight() + 'px', 'CCIframe');
      }
    }
  }
  this.hide = hide;
  function hide() {
    if(dateField) {
      setProperty('display', 'none');
      setElementProperty('display', 'none', 'CCIframe');
      dateField = null;
    }
  }
  this.visible = visible;
  function visible() {
    return dateField
  }
  this.can_hide = can_hide;
  var can_hide = 0;
}
var cC = new CC();
function date_picker(textField) {
  cC.show(textField);
}
function hideCC() {
  if (cC.visible()) {
    cC.hide();
  }
}
function setCCDate(year, month, day) {
  cC.setDate(year, month, day);
}
function changeCCYear(change) {
  cC.changeYear(change);
}
function changeCCMonth(change) {
  cC.changeMonth(change);
}
document.write(\"<iframe id='CCIframe' src='javascript:false;' frameBorder='0' scrolling='no'></iframe>\");
document.write(\"<div id='CC'></div>\");";

   $js_date_picker = $js;
   return '';
}

//
//  Javascript conversions to/from user numeric format.
//
function add_js_user_num() {
  global $thoseps, $decseps, $js_price_format;
  $ts = $thoseps[user_tho_sep()];
  $ds = $decseps[user_dec_sep()];
  $js_price_format = "
  function price_format(post, num, dec, label) {
    if(isNaN(num))
      num = \"0\";
    sign = (num == (num = Math.abs(num)));
    if(dec<0) dec = 2;
      decsize = Math.pow(10, dec);
    num = Math.floor(num*decsize+0.50000000001);
    cents = num%decsize;
    num = Math.floor(num/decsize).toString();
    for( i=cents.toString().length; i<dec; i++) {
      cents = \"0\" + cents;
    }
    for (var i = 0; i < Math.floor((num.length-(1+i))/3); i++)
      num = num.substring(0,num.length-(4*i+3))+'".$ts."'+
    num.substring(num.length-(4*i+3));
    num = ((sign)?'':'-') + num;
    if(dec!=0) num = num + '".$ds."' + cents;
      if(label)
        document.getElementById(post).innerHTML = num;
      else
        document.getElementsByName(post)[0].value = num;
  }
          
  function get_amount(doc, label) {
    if(label)
      var val = document.getElementById(doc).innerHTML;
    else
      var val = document.getElementsByName(doc)[0].value;
    val = val.replace(/\\".$ts."/g,'');
    val = val.replace(/\\".$ds."/g,'.');
    return 1*val;
  }
";
}

function add_js_allocate() {
  global $js_allocate;
  $js_allocate =
  "function allocate_all(doc) {
  var amount = get_amount('amount'+doc);
  var unallocated = get_amount('un_allocated'+doc);
  var total = get_amount('total_allocated', 1);
  var left = get_amount('left_to_allocate', 1);

  if(unallocated<amount) amount = unallocated;
  if((unallocated-amount)<=left){
      left-=unallocated-amount;
      total+=unallocated-amount;
      amount=unallocated;
  }else{
  total+=left;
  amount+=left;
  left=0;
  }
  price_format('amount'+doc, amount, ".user_price_dec().");
  price_format('left_to_allocate', left, ".user_price_dec().", 1);
  price_format('total_allocated', total, ".user_price_dec().", 1);
  }
  function allocate_none(doc) {
  amount = get_amount('amount'+doc);
  left = get_amount('left_to_allocate', 1);
  total = get_amount('total_allocated', 1);
  price_format('left_to_allocate',amount+left, ".user_price_dec().", 1);
  price_format('amount'+doc, 0, ".user_price_dec().");
  price_format('total_allocated', total-amount, ".user_price_dec().", 1);
  }";
}

function alert($msg)
{
  echo "\n<script type=\"text/javascript\">\n"
    . "<!--\n"
    . "alert('$msg');\n"
    . "-->\n"
    . "</script>\n";
}

if (!function_exists('_vd'))
{
    function _vd($mixed, $title = '', $exit = false)
    {
      // Only the site admin is able to proceed here.
      echo (!empty($title) ? ($title .':') : '') .'<pre>';
      var_dump($mixed);
      echo "</pre>\n";
      if ($exit)
        exit;
    }
}

?>
