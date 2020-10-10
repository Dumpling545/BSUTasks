package tp4_2;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;


public class MovingImageFrame extends JFrame implements ChangeListener, ActionListener{
	private JPanel contentPane;
	private MovingImagePanel movingImagePanel;
	private JSlider setVelocitySlider;
	private JLabel setVelocityLabel;
	private JLabel velocityTypeLabel;
	private JLabel directionLabel;
	
	private JRadioButton clockWiseDirectionRadioButton;
	private JRadioButton counterClockWiseDirectionRadioButton;
	
	private JRadioButton constantAnglePerPeriodRadioButton;
	private JRadioButton constantPixelsPerPeriodRadioButton;
		
	private final int VELOCITY_MAJOR_TICK = 4;
	private final int VELOCITY_MINOR_TICK = 2;
	private final int MIN_VELOCITY = 0;
	private final int MAX_VELOCITY = 40;
	public static void main(String[] args) {
		MovingImageFrame frame;
			try {
				frame = new MovingImageFrame();
				frame.setVisible(true);
			} catch (IOException e) {
				System.out.println(e.getMessage());
			}
			
	}
	public MovingImageFrame() throws IOException {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(640, 480);
		setTitle("Moving Image");
		contentPane = new JPanel();
		contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
		
		movingImagePanel = new MovingImagePanel();
		contentPane.add(movingImagePanel);
		setVelocityLabel = new JLabel("Velocity:");
		contentPane.add(setVelocityLabel);
		setVelocitySlider = new JSlider(MIN_VELOCITY, MAX_VELOCITY, movingImagePanel.getVelocity());
		contentPane.add(setVelocitySlider);
		setVelocitySlider.setMajorTickSpacing(VELOCITY_MAJOR_TICK);
		setVelocitySlider.setMinorTickSpacing(VELOCITY_MINOR_TICK);
		setVelocitySlider.setPaintTicks(true);
		setVelocitySlider.setPaintLabels(true);
		setVelocitySlider.addChangeListener(this);
		directionLabel = new JLabel("Direction:");
		clockWiseDirectionRadioButton = new JRadioButton("Clockwise direction");
		clockWiseDirectionRadioButton.setSelected(true);
		counterClockWiseDirectionRadioButton = new JRadioButton("Counterclockwise direction");
		clockWiseDirectionRadioButton.addActionListener(this);
		counterClockWiseDirectionRadioButton.addActionListener(this);
		ButtonGroup directionGroup = new ButtonGroup();
		directionGroup.add(clockWiseDirectionRadioButton);
		directionGroup.add(counterClockWiseDirectionRadioButton);
		contentPane.add(directionLabel);
		contentPane.add(clockWiseDirectionRadioButton);
		contentPane.add(counterClockWiseDirectionRadioButton);
		velocityTypeLabel = new JLabel("Velocity type:");
		constantAnglePerPeriodRadioButton = new JRadioButton("Constant angle per time period");
		constantAnglePerPeriodRadioButton.setSelected(true);
		constantPixelsPerPeriodRadioButton = new JRadioButton("Constant amount of pixels per time period");
		constantAnglePerPeriodRadioButton.addActionListener(this);
		constantPixelsPerPeriodRadioButton.addActionListener(this);
		ButtonGroup velocityTypeGroup = new ButtonGroup();
		velocityTypeGroup.add(constantAnglePerPeriodRadioButton);
		velocityTypeGroup.add(constantPixelsPerPeriodRadioButton);
		contentPane.add(velocityTypeLabel);
		contentPane.add(constantAnglePerPeriodRadioButton);
		contentPane.add(constantPixelsPerPeriodRadioButton);
		
		setContentPane(contentPane);
	}
	@Override
	public void stateChanged(ChangeEvent e) {
		movingImagePanel.setVelocity(setVelocitySlider.getValue());
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		if(clockWiseDirectionRadioButton.isSelected()) {
			movingImagePanel.setDirection(MovingImagePanel.CLOCKWISE_DIRECTION);
		} else {
			movingImagePanel.setDirection(MovingImagePanel.COUNTERCLOCKWISE_DIRECTION);
		}
		if(constantAnglePerPeriodRadioButton.isSelected()) {
			movingImagePanel.setVelocityType(MovingImagePanel.CONSTANT_ANGLE);
		} else {
			movingImagePanel.setVelocityType(MovingImagePanel.CONSTANT_PIXELS);
		}
	}
}
