<?php
namespace AFR\Controller;

class Rental extends BaseController
{
    protected function index()
    {
        $scope = new \stdClass;
        $scope->primus = 'sucks';
        $this->scope = $scope;
        return $scope;
    }    
    protected function edit($obj_id, $subview = 'location')
    {
        $logger = $this->app->logger;
        if(!$obj_id) { /** throw error */
            mydie("Controller Rental::edit: missing id");
        }
        
        /** replace this with fetch from Model */
        $scope = $this->scope = controller_rental_edit($this->app->site, $this->app->page, ['obj_id' => $obj_id]);
        
        $this->view = $scope->view = $subview = $subview ?: 'location';
        
        $rental= $scope->rental;
        
        $scope->subtemplate = $template_name = "components/_rental-edit-{$subview}.html";
        
        /** if subview not found, parse and copy to template dir */
        $logger->debug("Rental::edit view={$subview} obj_id:{$obj_id}");
        switch($subview) {
        case 'rate':
            break;
        case 'terms':
            break;
        case 'calendar':
            $scope->foobar = "foocal";
            break;
        default:
            break;
        }
        return $scope;
    }    
    protected function view()
    {
        $scope = new \stdClass;
        $scope->view = '1';
        $this->scope = $scope;
        return $scope;
    }    
    protected function search()
    {
        $scope = new \stdClass;
        $scope->search = '1';
        $this->scope = $scope;
        return $scope;
    }    
    
}

