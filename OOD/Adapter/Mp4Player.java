package Adapter;

public class Mp4Player implements AdvancedMediaPlayer{

  @Override
  public void playVLC( String fileName) {
    // TODO Auto-generated method stub
    throw new UnsupportedOperationException("Unimplemented method 'playVLC'");
  }

  @Override
  public void playMP4( String fileName) {
    System.out.println("Playing mp4 file. Name: "+ fileName);
  }
  
}
