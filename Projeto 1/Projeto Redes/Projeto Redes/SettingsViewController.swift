//
//  SettingsViewController.swift
//  Projeto Redes
//
//  Created by Erich Silveira on 15/05/17.
//  Copyright © 2017 LeonardoMaffei. All rights reserved.
//

import UIKit

class SettingsViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        
        
        // Do any additional setup after loading the view.
    }

    @IBAction func stepValueChanged(_ sender: Any) {
        
        
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func desconectPressed(_ sender: Any) {
        
        Client.sharedInstance.client.close()
        self.dismiss(animated: true, completion: nil)
        
    }

    
    @IBAction func sendToServerPressed(_ sender: Any) {
        
        print("sendPressed")
         let send = Client.sharedInstance.client.send(string: "5" )
        if(send.isSuccess) {
            print("Enviado com sucesso")
        }

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
