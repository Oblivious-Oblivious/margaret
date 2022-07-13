module Abstract
    def abstract_methods(*args)
        args.each do |name|
            class_eval(<<-END, __FILE__, __LINE__)
                def #{name}(*args)
                    raise NotImplementedError.new("Unimplemented #{name}(#{args}).");
                end
            END
        end
    end

    def error(message)
        raise StandardError.new message;
    end
end
