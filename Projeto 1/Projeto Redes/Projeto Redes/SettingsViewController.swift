//
//  SettingsViewController.swift
//  Projeto Redes
//
//  Created by Erich Silveira on 15/05/17.
//  Copyright © 2017 LeonardoMaffei. All rights reserved.
//

import UIKit

class SettingsViewController: UIViewController, UIPickerViewDataSource, UIPickerViewDelegate {

    @IBOutlet weak var wantedTemp: UILabel!
    @IBOutlet weak var pickerOutlet: UIPickerView!
    
    private var temp = 23
    
    
    var pickerDataSource = ["26", "25", "24", "23", "22", "21", "20", "19", "18", "16"];
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.pickerOutlet.dataSource = self;
        self.pickerOutlet.delegate = self;
        
        // Do any additional setup after loading the view.
    }
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return pickerDataSource.count;
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return pickerDataSource[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int)
    {
        if(row == 0)
        {
            self.view.backgroundColor = UIColor.init(colorLiteralRed: 255/255, green: 83/255, blue: 77/255, alpha: 1);
            temp = 26
            
        }
        else if(row == 1)
        {
            temp = 25

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 255/255, green: 123/255, blue: 118/255, alpha: 1);}
        else if(row == 2)
        {
            temp = 24

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 255/255, green: 141/255, blue: 137/255, alpha: 1);        }
        else if(row == 3)
        {
            temp = 23

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 255/255, green: 172/255, blue: 169/255, alpha: 1);
        }
        else if(row == 4)
        {
            temp = 22

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 254/255, green: 200/255, blue: 198/255, alpha: 1);
        }
        else if(row == 5)
        {
            temp = 21

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 255/255, green: 227/255, blue: 226/255, alpha: 1);        }
        else if(row == 6)
        {
            temp = 20

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 248/255, green: 253/255, blue: 255/255, alpha: 1);
            
        }
        else if(row == 7)
        {
            temp = 19

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 231/255, green: 249/255, blue: 255/255, alpha: 1);
            
        }
        else if(row == 8)
        {
            temp = 18

            self.view.backgroundColor =  UIColor.init(colorLiteralRed: 200/255, green: 242/255, blue: 255/255, alpha: 1);
            
        }
        else if(row == 9)
        {
            temp = 17

             self.view.backgroundColor = UIColor.init(colorLiteralRed: 174/255, green: 235/255, blue: 255/255, alpha: 1);
            
        }
        else
        {
            temp = 16

            self.view.backgroundColor = UIColor.init(colorLiteralRed: 142/255, green: 228/255, blue: 255/255, alpha: 1);
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func desconectPressed(_ sender: Any) {
        
        Client.sharedInstance.disconect()
        self.dismiss(animated: true, completion: nil)
        
    }

    
    @IBAction func sendToServerPressed(_ sender: Any) {
        
        wantedTemp.text = String(temp)
        print("sendPressed")
         let send = Client.sharedInstance.client.send(string: String(temp) )
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
