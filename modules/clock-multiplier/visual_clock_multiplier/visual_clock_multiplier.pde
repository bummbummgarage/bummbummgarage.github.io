
int start = 50;
int end = 750;
int cycle;

int quantity = 4;
float distribution = .5;

void setup() {
  
  size(800, 120);
  background(255);
  
}

void draw () {
  strokeWeight( 1 );
  line(start, 70, end, 70);
  stroke(0);
  
  cycle = end - start; 
  
  int[] slices = new int[quantity];
  
  // Cut slices.
  for(int i = 0; i < quantity; i++ ) {
    
    if (i==0) {
      
      slices[i] = int( distribution * ( cycle / quantity ) );
      
    } else {
      
      slices[i] = int( distribution * ( ( cycle - slices[i-1] ) / ( quantity - i ) ) + slices[i-1] );
      
    }
      
  }
  
  // Plot start and end line 
  line( start, 20, start, 60 );
  line( end, 20, end, 60 );
  
  // Plot slices.
  for(int i = 0; i < ( quantity - 1 ); i++ ) {
    
    int x = start + slices[i];
    line( x, 20, x, 60 );
    
  }
  
  // Add the labels
  String s = "Quantity: "+quantity+", distribution: "+distribution;
  textSize(20);
  text(s, start, 100); 
  fill(0);
  
  
  
}
