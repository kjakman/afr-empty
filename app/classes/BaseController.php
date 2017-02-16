<?php
namespace AFR\Controller;

abstract class BaseController
{
    protected $urlvalues;
    protected $action;
    protected $template;
    protected $app;
    protected $scope;
    
    public function __construct($app, $template, $action, $obj_id=0, $subview='')
    {
        $this->app = $app;
        $this->action = $action;
        $this->obj_id = $obj_id;
        $this->subview = $subview;
        $this->template = $template;
        $this->scope = [];
    }
    
    public function executeAction()
    {
        $this->scope = $scope = $this->{$this->action}($this->obj_id, $this->subview);
        return $this->scope;
    }
}
