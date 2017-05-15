//
//  ConectViewController.swift
//  Projeto Redes
//
//  Created by Leonardo Maffei on 15/05/17.
//  Copyright © 2017 LeonardoMaffei. All rights reserved.
//

import UIKit
import SwiftSocket

class ConectViewController: UIViewController {

    @IBOutlet weak var ipText: UITextField!
    @IBOutlet weak var portText: UITextField!
    @IBOutlet weak var conectButton: UIButton!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    
    @IBAction func ConectAction(_ sender: Any) {
    }
    
    
    
    
    

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
