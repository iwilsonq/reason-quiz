let valueFromEvent = (evt): string => evt->ReactEvent.Form.target##value;

[@react.component]
let make =
    (
      ~question: Question.t,
      ~onAddOption,
      ~onChangeQuestionTitle,
      ~onChangeQuestionOption,
    ) => {
  let renderOptions =
    question.options
    |> List.mapi((i, option: Question.questionOption) =>
         <div>
           <label htmlFor="options">
             <span>
               {"Option " ++ string_of_int(i + 1) |> React.string}
             </span>
             <br />
             <input
               type_="text"
               placeholder="an answer..."
               value={option.title}
               onChange={e =>
                 onChangeQuestionOption(
                   question.title,
                   option.title,
                   valueFromEvent(e),
                 )
               }
             />
           </label>
         </div>
       )
    |> Array.of_list
    |> React.array;

  <section>
    <div>
      <label htmlFor="question">
        <span> {"What do you want to ask?" |> React.string} </span>
        <br />
        <input
          type_="text"
          placeholder="the question..."
          value={question.title}
          onChange={e =>
            onChangeQuestionTitle(question.title, valueFromEvent(e))
          }
        />
      </label>
    </div>
    <div>
      <span> {"What are possible answers?" |> React.string} </span>
      renderOptions
    </div>
    <button onClick={_e => onAddOption(question.title)}>
      {"Add Option" |> React.string}
    </button>
  </section>;
};