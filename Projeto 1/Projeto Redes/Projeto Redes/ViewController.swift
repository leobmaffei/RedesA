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

    override func viewDidLoad() {
        super.viewDidLoad()
    
        // Do any additional setup after loading the view, typically from a nib.
        let client = TCPClient(address: "192.168.0.1", port: 5000)
        
        
        switch client.connect(timeout: 10) {
        case .success:
            print("Sucesso na conexão")
            
            break
        // Connection successful 🎉
        case .failure(let error):
            
            print("falha ao conectar ao cliente")
            break
            // 💩
        }
    }
    


    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

