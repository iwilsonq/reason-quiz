open Types;
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
    |> List.mapi((i, option: QuestionOption.t) =>
         <div className="mb-2" key={option.id}>
           <label htmlFor={option.id}>
             <div>
               <Text.Span> {"Option " ++ string_of_int(i + 1)} </Text.Span>
             </div>
             <Form.Input
               id={option.id}
               type_="text"
               placeholder="an answer..."
               value={option.title}
               onChange={e =>
                 onChangeQuestionOption(
                   question.id,
                   option.id,
                   valueFromEvent(e),
                 )
               }
             />
           </label>
         </div>
       )
    |> Array.of_list
    |> React.array;

  <section className="border-b-2 pb-4 mb-4 border-gray-200">
    <div className="mb-4">
      <label htmlFor={question.id}>
        <div>
          <Text.Span uppercase=true> "What do you want to ask?" </Text.Span>
        </div>
        <Form.Input
          id={question.id}
          type_="text"
          placeholder="the question..."
          value={question.title}
          onChange={e =>
            onChangeQuestionTitle(question.id, valueFromEvent(e))
          }
        />
      </label>
    </div>
    <div>
      <Text.Span uppercase=true> "What are possible answers?" </Text.Span>
      renderOptions
    </div>
    <Button
      title="Add Option"
      intent=Button.Link
      onClick={_e => onAddOption(question.title)}
    />
  </section>;
};