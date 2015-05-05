package TSort;

import javax.swing.*;
import javax.swing.GroupLayout.ParallelGroup;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.Dimension;
import java.io.IOException;

public class SortSelection extends JPanel implements ActionListener {
	protected JButton b1;
	//private JTextArea startPath, resultMessage;
	//private JPanel panel;

	public SortSelection()
	{
		b1 = new JButton("Select Folder");
		b1.setVerticalTextPosition(AbstractButton.CENTER);
		b1.setHorizontalTextPosition(AbstractButton.LEADING);
		b1.setMnemonic(KeyEvent.VK_D);
		b1.setActionCommand("folder");
		b1.addActionListener(this);
		b1.setToolTipText("Select folder directly above .tif and .wav files");

		

		// startPath = new JTextArea();
		// startPath.setColumns(1);
		// startPath.setLineWrap(false);
		// startPath.setRows(1);
		// startPath.setEditable(false);

		
		add(b1);
		
	}

	public void actionPerformed(ActionEvent e) {
		if("folder".equals(e.getActionCommand()))
		{
			chooseFolder();
		} 
	}

	public void chooseFolder()
	{
		JFileChooser fc = new JFileChooser();
		fc.setFileSelectionMode(fc.DIRECTORIES_ONLY);
		int returnVal = fc.showOpenDialog(this);
		if(returnVal == JFileChooser.APPROVE_OPTION)
		{
			System.out.println("You chose to open folder " + fc.getSelectedFile().getName());
			Sorter sorter = new Sorter(fc.getSelectedFile().getAbsolutePath());
			try{
			sorter.sortTiffAndWave();
			sorter.sortTiffFiles();
		}	catch (IOException e)
		{

		}
		}
	}
	private static void createAndShowGUI() {
		JFrame frame = new JFrame("Tiff and Wav Sorter");
		frame.setPreferredSize(new Dimension(400, 300));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		SortSelection newContentPane = new SortSelection();
		newContentPane.setOpaque(true);
		frame.setContentPane(newContentPane);

		frame.pack();
		frame.setVisible(true);
	}

	public static void main(String args[])
	{	
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				createAndShowGUI();
			}
		});
	}

}