import { FC } from "react";

import './LeftPanel.css';

export interface LeftPanelPropsType {
    isConnected: boolean;
    updateConnectHandler: () => void;
    constructions: Array<{ name: string; text: string }>;
    setConstructions: (name: string) => void;
    setConstruction: (index: number) => void;
}

const LeftPanel: FC<LeftPanelPropsType> = (props: LeftPanelPropsType) => {
    const addConstruction = () => {
        props.setConstructions(`New construction ${props.constructions.length + 1}`);
    }
    
    return(
    <div className="left-panel">
        <div className="connection-status">
            <h2
                className={props.isConnected ? 'success-connect' : 'errored-connect'}
                onClick={props.updateConnectHandler}
            >
                {props.isConnected ? 'Соединение установлено' : 'Нет соединения с БЗ'}
            </h2>
        </div>
        <div className="constructions">
            {
                props.constructions.map((construction, i) => (
                    <div onClick={() => { props.setConstruction(i) }} className="construction" key={`construction-${i}-${construction.name}`}>
                        <p>{construction.name}</p>
                    </div>
                ))
            }
        </div>
        <button
            className="add-construction"
            onClick={(e) => { addConstruction() }}
        >
            Add construction
        </button>
    </div>
    );
};

export default LeftPanel;