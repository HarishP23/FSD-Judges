import { Component } from '@angular/core';

@Component({
  selector: 'app-landing',
  standalone: false,
  templateUrl: './landing.component.html',
  styleUrls: ['./landing.component.css']
})
export class LandingComponent {
  // Variable to control the visibility of the form
  isFormVisible = false;

  // Method to toggle the form visibility
  toggleForm() {
    this.isFormVisible = !this.isFormVisible;
  }
}
