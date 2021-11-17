import { Component, OnInit } from '@angular/core';
import { HTTP } from '@ionic-native/http/ngx';

import { environment } from '../../environments/environment';


@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage implements OnInit {

  constructor(
    private http: HTTP
  ) { }

  ngOnInit() {
  }

  etatProjecteurFond: boolean;
  etatProjecteurRondPoint: boolean;

  toggleAll: boolean;

  public changeDisplayedFormat(formatID: number) {

    switch (formatID) {
      case 0:
        this.http.get(environment.serverIP + "seconds", {}, {}).then(response => {
          console.log(response);
        });

        break;
      case 1:
        this.http.get(environment.serverIP + "minutes", {}, {}).then(response => {
          console.log(response);
        });

        break;
      case 2:
        this.http.get(environment.serverIP + "hours", {}, {}).then(response => {
          console.log(response);
        });

        break;
      case 3:
        this.http.get(environment.serverIP + "days", {}, {}).then(response => {
          console.log(response);
        });

        break;
      case 4:
        this.http.get(environment.serverIP + "weeks", {}, {}).then(response => {
          console.log(response);
        });

        break;
        case 5:
        this.http.get(environment.serverIP + "months", {}, {}).then(response => {
          console.log(response);
        });

        break;
        case 6:
        this.http.get(environment.serverIP + "years", {}, {}).then(response => {
          console.log(response);
        });

        break;

      default:
        break;
    }




  }


}