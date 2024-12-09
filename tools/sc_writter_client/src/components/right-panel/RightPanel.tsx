import { FC } from "react";

import './RightPanel.css';

type RightPanelType = {
    selectedConstruction: {
        name: string;
        text: string;
    },
    index: number;
    onChangeName: (name: string, i: number) => void;
    onChangeText: (text: string, i: number) => void;
    handleUpload: (index: number) => Promise<void>;
}

const RightPanel: FC<RightPanelType> = (props: RightPanelType) => (
    <div className="right-panel">
        <input onChange={(e) => { props.onChangeName(e.target.value, props.index) }} type="text" value={props.selectedConstruction.name}/>
        <textarea onChange={(e) => { props.onChangeText(e.target.value, props.index) }} value={props.selectedConstruction.text}></textarea>
        <button
            className="add-construction"
            onClick={(e) => { props.handleUpload(props.index) }}
        >
            Upload
        </button>
    </div>
);

export default RightPanel;