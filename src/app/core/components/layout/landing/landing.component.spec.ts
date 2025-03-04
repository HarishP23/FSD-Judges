import { ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { LandingComponent } from './landing.component';

describe('LandingComponent', () => {
  let component: LandingComponent;
  let fixture: ComponentFixture<LandingComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [LandingComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(LandingComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });

  it('should toggle form visibility when button is clicked', () => {
    // Initially, the form should be hidden
    expect(component.isFormVisible).toBeFalse();

    // Get the button element and click it
    const button = fixture.debugElement.query(By.css('.open-form-btn'));
    button.triggerEventHandler('click', null);

    // After the button click, form should be visible
    expect(component.isFormVisible).toBeTrue();

    // Click the button again to hide the form
    button.triggerEventHandler('click', null);

    // After the second click, form should be hidden again
    expect(component.isFormVisible).toBeFalse();
  });
});
