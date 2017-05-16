//
//  ViewController.swift
//  Projeto Redes
//
//  Created by Leonardo Maffei on 02/05/17.
//  Copyright © 2017 LeonardoMaffei. All rights reserved.
//

import UIKit
import SwiftSocket

class ViewController: UIViewController {

    
    @IBOutlet weak var portText: UITextField!
    @IBOutlet weak var ipText: UITextField!
    @IBOutlet weak var conectButton: UIButton!
    @IBOutlet weak var SendButton: UIButton!
    @IBOutlet weak var conectionLabel: UILabel!
    
    
    
    
    
    
    var ipToConnect = "192.168.1.100"
    var portToConnect:Int32 = 5000
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
    
        
        
        
        // Do any additional setup after loading the view, typically from a nib.
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: "dismissKeyboard")
        
        view.addGestureRecognizer(tap)
        
    
    }

    @IBAction func conectToServer(_ sender: Any) {
        
        
       ipToConnect = ipText.text!
       portToConnect = Int32(portText.text!)!
        
        Client.sharedInstance.setupClient(ip: ipToConnect, port: portToConnect)
        
        switch Client.sharedInstance.client.connect(timeout: 10) {
        case .success:
            let send = Client.sharedInstance.client.send(string: "9" )
            
            
            
            if(send.isSuccess) {
                print("Sucesso na conexão")
            }
            conectionLabel.text = "Conectado"
            
            self.performSegue(withIdentifier: "showSettings", sender: self)
            
            break
        // Connection successful 🎉
        case .failure(let error):
            
            print("falha ao conectar ao cliente")
            conectionLabel.text = "Falha ao conectar"
            
            break
            // 💩
        }
        
    
    }
    
    @IBAction func sendData(_ sender: Any) {
        switch Client.sharedInstance.client.send(string: "9" ){
        case .success:
            print("mensagem enviada")
        case .failure(let error):
            print("erro no envio")
        }
    }
    
    func dismissKeyboard() {
        //Causes the view (or one of its embedded text fields) to resign the first responder status.
        view.endEditing(true)
    }


    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func applicationWillTerminate(application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
        
        Client.sharedInstance.client.close()
    }


}

