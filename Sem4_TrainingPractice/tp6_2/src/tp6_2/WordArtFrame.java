package tp6_2;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GraphicsConfiguration;
import java.awt.GridLayout;

import javax.media.j3d.*;
import javax.vecmath.*;

import com.sun.j3d.utils.universe.SimpleUniverse;
import com.sun.j3d.utils.universe.Viewer;
import com.sun.j3d.utils.universe.ViewingPlatform;

public class WordArtFrame extends JFrame implements CaretListener, ChangeListener{
	private JPanel canvasPanel;
	private JPanel toolPanel;
	private JPanel textOptionsPanel;
	private JTextField textEditingField;
	private JColorChooser textColorChooser;
	private JSlider[][] lightPositionSliders;
	private final String[] sliderCoordinateNames = {"X Axis:", "Y Axis:", "Z Axis:"};
	static final int[] MIN_SLIDER_COORDINATE = {-1000, -1000, -1000};
	static final int[] MAX_SLIDER_COORDINATE = {1000, 1000, 1000};
	static final float CONVERT_COEFFICIENT = 0.1f;
	static final int[][] LIGHT_INIT_SLIDER_DIRECTION = {{1000, 0, -200}, {-100,-100, -200}};
	private PointLight[] lights;
	private JPanel[] lightOptionsPanel;
	private BranchGroup mainGroup;
	private Text3D text;
	private Material textMaterial;
	private final Color DEFAULT_TEXT_COLOR = Color.BLUE;
	private final Color DEFAULT_LIGHT_COLOR = Color.WHITE;
	public WordArtFrame() {
		JPanel contentPane = new JPanel();
		contentPane.setLayout(new GridLayout(2, 1));
		canvasPanel = new JPanel();
		canvasPanel.setLayout(new GridLayout(1, 1, 2, 2));
		GraphicsConfiguration config = SimpleUniverse
				.getPreferredConfiguration();
		Canvas3D canvas3D = new Canvas3D(config);
		ViewingPlatform viewingPlatform = new ViewingPlatform();
	    viewingPlatform.getViewPlatform().setActivationRadius(300f);
	    TransformGroup viewTransform = viewingPlatform.getViewPlatformTransform();
	    Transform3D t3d = new Transform3D();
	    t3d.lookAt(new Point3d(0,0,10), new Point3d(0,0,0), new Vector3d(0,1,0));
	    t3d.invert();
	    viewTransform.setTransform(t3d);
	    Viewer viewer = new Viewer(canvas3D);
	    View view = viewer.getView();
	    view.setBackClipDistance(300);
	    SimpleUniverse universe = new SimpleUniverse(viewingPlatform, viewer);
		mainGroup = new BranchGroup();
		initText(mainGroup);
		addLights(mainGroup);
		
		universe.addBranchGraph(mainGroup);
		canvasPanel.add(canvas3D);
		contentPane.add(canvasPanel);
		toolPanel = new JPanel();
		toolPanel.setLayout(new GridLayout(1, 3));
		textOptionsPanel = new JPanel();
		textOptionsPanel.setLayout(new BoxLayout(textOptionsPanel, BoxLayout.Y_AXIS));
		textOptionsPanel.setBorder(BorderFactory.createLineBorder(Color.black));
		JLabel textOptionsLabel = new JLabel("TEXT OPTIONS:");
		textOptionsPanel.add(textOptionsLabel);
		JLabel contentLabel = new JLabel("Content:");
		textOptionsPanel.add(contentLabel);
		textEditingField = new JTextField();
		textEditingField.addCaretListener(this);
		textOptionsPanel.add(textEditingField);
		JLabel textColorLabel = new JLabel("Color:");
		textOptionsPanel.add(textColorLabel);
		textColorChooser = new JColorChooser(DEFAULT_TEXT_COLOR);
		textColorChooser.setPreviewPanel(new JPanel());
		textColorChooser.getSelectionModel().addChangeListener(this);
		textOptionsPanel.add(textColorChooser);
		toolPanel.add(textOptionsPanel);
		lightOptionsPanel = new JPanel[2];
		lightPositionSliders = new JSlider[2][3];
		for(int i = 0; i < 2; i++) {
			lightOptionsPanel[i] = new JPanel();
			lightOptionsPanel[i].setLayout(new BoxLayout(lightOptionsPanel[i], BoxLayout.Y_AXIS));
			lightOptionsPanel[i].setBorder(BorderFactory.createLineBorder(Color.black));
			JLabel lightOptionsLabel = new JLabel("LIGHT#"+ (i + 1) +" OPTIONS:");
			lightOptionsPanel[i].add(lightOptionsLabel);
			for(int j = 0; j < 3; j++) {
				lightPositionSliders[i][j] = new JSlider(JSlider.HORIZONTAL, 
						MIN_SLIDER_COORDINATE[j], MAX_SLIDER_COORDINATE[j], LIGHT_INIT_SLIDER_DIRECTION[i][j]);
				lightPositionSliders[i][j].addChangeListener(this);
				lightOptionsPanel[i].add(new JLabel(sliderCoordinateNames[j]));
				lightOptionsPanel[i].add(lightPositionSliders[i][j]);
			}
			toolPanel.add(lightOptionsPanel[i]);
		}
		contentPane.add(toolPanel);
		setContentPane(contentPane);
		pack();
	}
	public static void main(String[] args) {
		WordArtFrame waframe = new WordArtFrame();
		waframe.setVisible(true);
    }
	public void addLights(BranchGroup group) {
		BoundingSphere bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0),
				1000.0);
		lights = new PointLight[2];
		for(int i = 0; i < 2; i++) {
			Color3f color = new Color3f(DEFAULT_LIGHT_COLOR);
			Point3f position = convertSliderCoordinatesIntoPoint3f(LIGHT_INIT_SLIDER_DIRECTION[i]);
			Point3f atten = new Point3f(0.2f, 0f, 0f);
			lights[i] = new PointLight(color, position, atten);
			lights[i].setInfluencingBounds(bounds);
			lights[i].setCapability(PointLight.ALLOW_POSITION_WRITE);
			group.addChild(lights[i]);
		}		
		Color3f ambientColor = new Color3f(.2f, .2f, .2f);
		AmbientLight ambientLightNode = new AmbientLight(ambientColor);
		ambientLightNode.setInfluencingBounds(bounds);
		group.addChild(ambientLightNode);
	}

	
	private Point3f convertSliderCoordinatesIntoPoint3f(int [] sliderCoordinates) {
		float[] result = new float[3];
		for(int i = 0 ; i < 3; i++) {
			result[i] = sliderCoordinates[i] * CONVERT_COEFFICIENT;
		}
		return new Point3f(result);
	}
	private Point3f convertSliderCoordinatesIntoPoint3f(JSlider [] sliders) {
		return convertSliderCoordinatesIntoPoint3f(new int[]{sliders[0].getValue(), 
												   sliders[1].getValue(),
												   sliders[2].getValue()});
	}
	private void initText(BranchGroup group) {
		Font3D f3d = new Font3D(new Font("TestFont", Font.PLAIN, 2),
				new FontExtrusion());
		Point3f position = new Point3f(-1.5f, -.5f, -10);
		text = new Text3D(f3d, null, position);
		text.setCapability(Text3D.ALLOW_STRING_WRITE);
		text.setCapabilityIsFrequent(Text3D.ALLOW_STRING_WRITE);
		text.setCapability(Text3D.ALLOW_STRING_READ);
		text.setCapabilityIsFrequent(Text3D.ALLOW_STRING_READ);
		text.setCapability(Text3D.ALLOW_POSITION_WRITE);
		text.setCapabilityIsFrequent(Text3D.ALLOW_POSITION_WRITE);
		Color3f white = new Color3f(1.0f, 1.0f, 1.0f);
		Color3f blue = new Color3f(DEFAULT_TEXT_COLOR);
		Appearance a = new Appearance();
		textMaterial = new Material(blue, blue, blue, white, 80.0f);
		textMaterial.setLightingEnable(true);
		textMaterial.setCapability(Material.ALLOW_COMPONENT_WRITE);
		textMaterial.setCapabilityIsFrequent(Material.ALLOW_COMPONENT_WRITE);
		a.setMaterial(textMaterial);
		Shape3D sh = new Shape3D();
		sh.setGeometry(text);
		sh.setAppearance(a);
		TransformGroup tg = new TransformGroup();
		Transform3D rot = new Transform3D();
		rot.rotX(Math.PI / 3);
		rot.rotY(Math.PI / 5);
		tg.setTransform(rot);
		tg.addChild(sh);
		group.addChild(tg);
	}
	@Override
	public void caretUpdate(CaretEvent e) {
		text.setString(textEditingField.getText());
	}
	@Override
	public void stateChanged(ChangeEvent e) {
		if(e.getSource() == textColorChooser.getSelectionModel()) {
			Color3f newColor = new Color3f(textColorChooser.getColor());
			textMaterial.setAmbientColor(newColor);
			textMaterial.setDiffuseColor(newColor);
			textMaterial.setEmissiveColor(newColor);
		} else {
			for(int i = 0; i < 2; i++) {
				for(int j = 0; j < 3; j++) {
					if(e.getSource() == lightPositionSliders[i][j]) {
						Point3f point = convertSliderCoordinatesIntoPoint3f(lightPositionSliders[i]);
						lights[i].setPosition(point);
						break;
					}
				}
			}
		}
	}
}
